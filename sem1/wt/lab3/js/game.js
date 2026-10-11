// Aditya 
// "My Library" box is written by Jayshree
// The details page of one game. The id comes from the url, like game.html?id=3498

import { getGameDetails, getScreenshots, getStoreLinks } from './api.js';
import { smallImage, starText, scoreBox } from './card.js';
import { getUser } from './auth.js';
import { supabase } from './config.js';
import { getStatus, saveToLibrary, removeFromLibrary } from './db.js';
import { setupMenu } from './menu.js';

setupMenu();

var box = document.getElementById('game-details');
var params = new URLSearchParams(window.location.search);
var gameId = params.get('id');

var game = null;

// join the names in a list, like "PC, Xbox, PlayStation"
function joinNames(items) {
  var names = [];
  for (var i = 0; i < items.length; i++) {
    names.push(items[i].name);
  }
  return names.join(', ');
}

// a small box with a label and a value, like "Released / 17 September 2013"
function factBox(label, value) {
  return '<div class="fact"><span>' + label + '</span><b>' + value + '</b></div>';
}

async function showGame() {
  if (!gameId) {
    box.innerHTML = '<p class="message">No game selected. <a href="games.html">Go to the browse page</a>.</p>';
    return;
  }

  try {
    game = await getGameDetails(gameId);
  } catch (error) {
    console.log(error);
    box.innerHTML = '<p class="message">Sorry, could not load this game.</p>';
    return;
  }

  document.title = game.name + ' - Quest';

  // genres and tags as small chips
  var chips = '';
  for (var i = 0; i < game.genres.length; i++) {
    chips += '<span class="tag">' + game.genres[i].name + '</span>';
  }

  var released = 'Unknown';
  if (game.released) {
    released = new Date(game.released).toLocaleDateString('en-GB', { day: 'numeric', month: 'long', year: 'numeric' });
  }

  var platformChips = '';
  for (var p = 0; p < (game.platforms || []).length; p++) {
    platformChips += '<span class="tag plain">' + game.platforms[p].platform.name + '</span>';
  }

  var html = '';
  html += '<div class="game-layout">';

  // ----- left side -----
  html += '<div class="game-main">';
  html += '  <img class="cover" src="' + smallImage(game.background_image) + '" alt="' + game.name + '">';
  html += '  <h1>' + game.name + '</h1>';
  html += '  <div class="rating-line"><span class="big-stars">' + starText(game.rating) + '</span> <b>' + game.rating + '</b> <span class="muted">from ' + game.ratings_count.toLocaleString() + ' ratings on RAWG</span></div>';
  html += '  <div class="chip-row">' + chips + '</div>';

  html += '  <div class="facts-grid">';
  html += factBox('Released', released);
  html += factBox('Average playtime', game.playtime ? 'About ' + game.playtime + ' hours' : 'N/A');
  html += factBox('Metacritic', game.metacritic ? scoreBox(game.metacritic) : 'N/A');
  html += factBox('Developer', joinNames(game.developers || []) || 'Unknown');
  html += factBox('Publisher', joinNames(game.publishers || []) || 'Unknown');
  html += factBox('Age rating', game.esrb_rating ? game.esrb_rating.name : 'Not rated');
  html += '  </div>';

  html += '  <h2>Platforms</h2>';
  html += '  <div class="chip-row">' + platformChips + '</div>';

  html += '  <div id="screenshots"></div>';

  html += '  <h2>About this game</h2>';
  html += '  <p id="description-text" class="about-text"></p>';
  html += '</div>';

  // ----- right side -----
  html += '<aside class="game-side">';
  html += '  <div class="side-box" id="library-box"></div>';
  html += '  <div class="side-box" id="store-box"></div>';
  html += '</aside>';

  html += '</div>';
  box.innerHTML = html;

  // description is plain text from RAWG
  document.getElementById('description-text').textContent = game.description_raw || 'No description available.';

  showLibraryBox();
  showStores();
  showScreenshots();
}

// the screenshots: one big picture and small pictures below it
async function showScreenshots() {
  var shots = await getScreenshots(game.id);
  if (shots.length == 0) {
    return;
  }

  var html = '<h2>Screenshots</h2>';
  html += '<img id="big-shot" class="cover" src="' + shots[0].image + '" alt="Screenshot of ' + game.name + '">';
  html += '<div class="thumbs">';
  for (var i = 0; i < shots.length && i < 6; i++) {
    html += '<img class="thumb' + (i == 0 ? ' active' : '') + '" src="' + shots[i].image + '" alt="Screenshot ' + (i + 1) + '">';
  }
  html += '</div>';
  document.getElementById('screenshots').innerHTML = html;

  // clicking a small picture shows it big
  var thumbs = document.querySelectorAll('.thumb');
  for (var t = 0; t < thumbs.length; t++) {
    thumbs[t].addEventListener('click', function (event) {
      document.getElementById('big-shot').src = event.target.src;
      for (var k = 0; k < thumbs.length; k++) {
        thumbs[k].classList.remove('active');
      }
      event.target.classList.add('active');
    });
  }
}

// the "Where to buy" box
async function showStores() {
  var storeBox = document.getElementById('store-box');
  var links = await getStoreLinks(game.id);

  // RAWG gives the links with a store id, the names are in game.stores
  var names = {};
  var storeList = game.stores || [];
  for (var i = 0; i < storeList.length; i++) {
    names[storeList[i].store.id] = storeList[i].store.name;
  }

  var buttons = '';
  for (var j = 0; j < links.length; j++) {
    var url = links[j].url;
    var name = names[links[j].store_id];
    // only normal web links are allowed
    if (name && url && (url.startsWith('http://') || url.startsWith('https://'))) {
      buttons += '<a class="store-link" href="' + url + '" target="_blank" rel="noopener noreferrer">Get on ' + name + '<span>&#8599;</span></a>';
    }
  }

  var html = '<h2>Get the game</h2>';
  if (buttons != '') {
    html += '<p class="muted">Available on:</p>' + buttons;
  } else if (storeList.length > 0) {
    // no links from RAWG: show the store names without links
    var chips = '';
    for (var s = 0; s < storeList.length; s++) {
      chips += '<span class="tag plain">' + storeList[s].store.name + '</span>';
    }
    html += '<p class="muted">Sold on these stores (RAWG did not give direct links for this game):</p>';
    html += '<div class="chip-row">' + chips + '</div>';
  } else {
    html += '<p class="muted">No store information is available for this game.</p>';
  }

  if (game.website && (game.website.startsWith('http://') || game.website.startsWith('https://'))) {
    html += '<a class="store-link website" href="' + game.website + '" target="_blank" rel="noopener noreferrer">Official website<span>&#8599;</span></a>';
  }
  storeBox.innerHTML = html;
}

// the box where the user can add the game to their library
async function showLibraryBox() {
  var libraryBox = document.getElementById('library-box');

  if (!supabase) {
    libraryBox.innerHTML = '<h2>My Library</h2><p class="muted">The library is not set up yet (supabase keys are missing).</p>';
    return;
  }

  var user = await getUser();
  if (!user) {
    var here = encodeURIComponent('game.html?id=' + game.id);
    var html = '<h2>Save this game</h2>';
    html += '<p class="muted">Log in to add it to your library and track your progress.</p>';
    html += '<a href="login.html?next=' + here + '" class="button full">Log in</a>';
    html += '<a href="login.html?mode=signup&next=' + here + '" class="button outline full">Create an account</a>';
    libraryBox.innerHTML = html;
    return;
  }

  var status = await getStatus(game.id);

  var boxHtml = '<h2>My Library</h2>';
  boxHtml += '<p id="library-text" class="muted"></p>';
  boxHtml += '<select id="status-select" class="full">';
  boxHtml += '  <option value="want-to-play">Want to Play</option>';
  boxHtml += '  <option value="playing">Playing</option>';
  boxHtml += '  <option value="completed">Completed</option>';
  boxHtml += '</select>';
  boxHtml += '<button id="save-button" class="button full"></button>';
  boxHtml += '<button id="remove-button" class="button outline full">Remove from library</button>';
  libraryBox.innerHTML = boxHtml;

  var select = document.getElementById('status-select');
  var saveButton = document.getElementById('save-button');
  var removeButton = document.getElementById('remove-button');
  var text = document.getElementById('library-text');

  // set the box to match the current status
  function updateBox() {
    if (status) {
      select.value = status;
      saveButton.textContent = 'Update status';
      removeButton.hidden = false;
      text.textContent = 'This game is in your library.';
    } else {
      saveButton.textContent = 'Add to library';
      removeButton.hidden = true;
      text.textContent = 'Choose a list for this game:';
    }
  }
  updateBox();

  saveButton.addEventListener('click', async function () {
    try {
      await saveToLibrary(game, select.value);
      status = select.value;
      updateBox();
      text.textContent = 'Saved to your library!';
    } catch (error) {
      console.log(error);
      text.textContent = 'Something went wrong. Did you run the library.sql file in supabase?';
    }
  });

  removeButton.addEventListener('click', async function () {
    try {
      await removeFromLibrary(game.id);
      status = null;
      updateBox();
      text.textContent = 'Removed from your library.';
    } catch (error) {
      console.log(error);
      text.textContent = 'Something went wrong.';
    }
  });
}

showGame();
