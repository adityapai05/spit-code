// Yuvraj
// The recommender on the home page. Steps:
//   1. the user types what they want to play
//   2. gemini.js turns the sentence into filters (genres and tags)
//   3. we ask RAWG for games with those filters
//   4. we show the games and a small "why" line under each one

import { getGames, getGameDetails } from './api.js';
import { understandRequest } from './gemini.js';
import { makeCard, markSavedGames } from './card.js';

var section = document.getElementById('results-section');
var statusBox = document.getElementById('status');
var understoodBox = document.getElementById('understood');
var resultsBox = document.getElementById('results');

// turn a slug like "story-rich" into "Story Rich" to show on the screen
function prettyName(slug) {
  if (slug == 'role-playing-games-rpg') {
    return 'RPG';
  }
  var words = slug.split('-');
  for (var i = 0; i < words.length; i++) {
    words[i] = words[i].charAt(0).toUpperCase() + words[i].slice(1);
  }
  return words.join(' ');
}

// show the filters we found as small chips
function showUnderstood(prefs, referenceName) {
  understoodBox.innerHTML = '';
  var all = prefs.genres.concat(prefs.tags);
  if (all.length == 0 && !referenceName) {
    return;
  }

  var title = document.createElement('span');
  title.className = 'understood-title';
  title.textContent = 'We looked for:';
  understoodBox.appendChild(title);

  if (referenceName) {
    var ref = document.createElement('span');
    ref.className = 'chip chip-ref';
    ref.textContent = 'Like ' + referenceName;
    understoodBox.appendChild(ref);
  }
  for (var i = 0; i < all.length; i++) {
    var chip = document.createElement('span');
    chip.className = 'chip';
    chip.textContent = prettyName(all[i]);
    understoodBox.appendChild(chip);
  }
}

// make the "why this game" sentence using the data RAWG gave us
function makeReason(game, prefs, referenceName) {
  var matches = [];
  var i;

  for (i = 0; i < (game.genres || []).length; i++) {
    if (prefs.genres.includes(game.genres[i].slug)) {
      matches.push(game.genres[i].name);
    }
  }
  for (i = 0; i < (game.tags || []).length; i++) {
    if (prefs.tags.includes(game.tags[i].slug)) {
      matches.push(game.tags[i].name);
    }
  }

  if (matches.length > 0) {
    return 'Matches: ' + matches.slice(0, 4).join(', ');
  }
  if (referenceName) {
    return 'Similar to ' + referenceName;
  }
  return 'Popular game that fits your search';
}

// ask RAWG for games. If we get nothing, we try again with fewer filters.
async function findGames(prefs, referenceId) {
  var genre = prefs.genres.join(',');
  var tags = prefs.tags.join(',');

  var attempts = [
    { genre: genre, tags: tags },
    { genre: genre, tags: '' },
    { genre: '', tags: tags },
  ];

  for (var i = 0; i < attempts.length; i++) {
    if (attempts[i].genre == '' && attempts[i].tags == '') {
      continue;
    }
    var data = await getGames({
      genre: attempts[i].genre,
      tags: attempts[i].tags,
      ordering: '-added',
      pageSize: 13,
    });

    // do not recommend the same game the user mentioned
    var games = data.results.filter(function (g) {
      return g.id != referenceId;
    });
    if (games.length > 0) {
      return games.slice(0, 12);
    }
  }
  return [];
}

// home.js calls this when the user searches
export async function runSearch(text) {
  section.hidden = false;
  resultsBox.innerHTML = '';
  understoodBox.innerHTML = '';
  statusBox.textContent = 'Thinking about your request...';
  section.scrollIntoView();

  try {
    // step 1: gemini turns the sentence into filters
    var prefs = await understandRequest(text);
    var usedGemini = true;
    if (prefs == null) {
      usedGemini = false;
      prefs = { genres: [], tags: [], similarTo: '', summary: '' };
    }

    // step 2: if the user said "like <game>" we look at that game's genres and tags
    var referenceName = '';
    var referenceId = 0;
    if (prefs.similarTo) {
      var found = await getGames({ search: prefs.similarTo, pageSize: 1 });
      if (found.results.length > 0) {
        var details = await getGameDetails(found.results[0].id);
        referenceName = details.name;
        referenceId = details.id;
        if (prefs.genres.length == 0) {
          for (var i = 0; i < details.genres.length && i < 2; i++) {
            prefs.genres.push(details.genres[i].slug);
          }
        }
        if (prefs.tags.length == 0) {
          for (var j = 0; j < details.tags.length && prefs.tags.length < 3; j++) {
            prefs.tags.push(details.tags[j].slug);
          }
        }
      }
    }

    // step 3: ask RAWG for the games
    var games = [];
    if (usedGemini) {
      games = await findGames(prefs, referenceId);
    }
    // if gemini did not work, or nothing was found, we just search RAWG with the words
    var note = '';
    if (games.length == 0) {
      var data = await getGames({ search: text, pageSize: 12 });
      games = data.results;
      if (!usedGemini) {
        note = 'The AI part is not available right now, so we searched using your words directly.';
      }
    }

    // step 4: show everything
    if (games.length == 0) {
      statusBox.textContent = 'No games found. Try describing it in a different way.';
      return;
    }

    statusBox.textContent = (prefs.summary + ' ' + note).trim() || 'Here are some games for you:';
    showUnderstood(prefs, referenceName);

    var html = '';
    for (var k = 0; k < games.length; k++) {
      html = html + makeCard(games[k], makeReason(games[k], prefs, referenceName));
    }
    resultsBox.innerHTML = html;
    markSavedGames();
  } catch (error) {
    console.log(error);
    statusBox.textContent = 'Sorry, something went wrong. Check the RAWG key in the .env file and try again.';
  }
}
