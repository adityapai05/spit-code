// Yuvraj
// Makes the game cards (used on the home page and the browse page) and the small
// "add to library" button on the top right of every card.

import { getUser } from './auth.js';
import { supabase } from './config.js';
import { getLibrary, saveToLibrary, removeFromLibrary, statusNames } from './db.js';

var knownGames = {};      // game id -> game data (the button needs the name and image to save)
var libraryPromise = null; // game id -> status, loaded only once
var loggedIn = false;

// RAWG images are very big, so this changes the link to get a smaller image
export function smallImage(url) {
  if (!url) {
    return 'images/placeholder.svg';
  }
  return url.replace('/media/games/', '/media/crop/600/400/games/');
}

// Converts rating to stars
export function starText(rating) {
  var full = Math.round(rating);
  var text = '';
  for (var i = 1; i <= 5; i++) {
    text += i <= full ? '★' : '☆';
  }
  return text;
}

// the coloured Metacritic box: green, yellow or red
export function scoreBox(score) {
  if (!score) {
    return '';
  }
  var colour = 'good';
  if (score < 75) {
    colour = 'ok';
  }
  if (score < 50) {
    colour = 'bad';
  }
  return '<span class="score ' + colour + '" title="Metacritic score">' + score + '</span>';
}

// "PC · PlayStation · Xbox" from the parent_platforms list of RAWG
function platformText(game) {
  var names = [];
  var list = game.parent_platforms || [];
  for (var i = 0; i < list.length && i < 4; i++) {
    var name = list[i].platform.name;
    if (name == 'Apple Macintosh') {
      name = 'Mac';
    }
    names.push(name);
  }
  return names.join(' · ');
}

// reason is optional. The home page recommender uses it to show why the game was suggested.
export function makeCard(game, reason) {
  knownGames[game.id] = game;

  var genres = [];
  for (var i = 0; i < (game.genres || []).length && i < 2; i++) {
    genres.push(game.genres[i].name);
  }

  var rating = game.rating ? game.rating.toFixed(1) : 'N/A';
  var year = game.released ? game.released.slice(0, 4) : 'TBA';
  var link = 'game.html?id=' + game.id;

  var html = '';
  html += '<div class="card">';
  html += '  <div class="card-image">';
  html += '    <a href="' + link + '"><img src="' + smallImage(game.background_image) + '" alt="' + game.name + '" loading="lazy"></a>';
  html += '    <button class="save-button" data-id="' + game.id + '" title="Add to library" aria-label="Add to library">';
  html += '      <svg viewBox="0 0 24 24" width="20" height="20"><path d="M6 3h12a1 1 0 0 1 1 1v17l-7-4-7 4V4a1 1 0 0 1 1-1z"/></svg>';
  html += '    </button>';
  html += '  </div>';
  html += '  <div class="card-body">';
  html += '    <h3><a href="' + link + '">' + game.name + '</a></h3>';
  html += '    <div class="card-meta">';
  html += '      <span class="stars">★ ' + rating + '</span>';
  html += '      <span>' + year + '</span>';
  if (game.playtime) {
    html += '      <span>~' + game.playtime + ' hrs</span>';
  }
  html += '      ' + scoreBox(game.metacritic);
  html += '    </div>';
  html += '    <p class="card-genres">' + genres.join(', ') + '</p>';
  html += '    <p class="card-platforms">' + platformText(game) + '</p>';
  if (reason) {
    html += '    <p class="card-reason">' + reason + '</p>';
  }
  html += '  </div>';
  html += '</div>';
  return html;
}

// ---------- the add to library button ----------

// gets the library of the logged in user (only once, then we reuse it)
function loadLibraryMap() {
  if (libraryPromise == null) {
    libraryPromise = fetchLibraryMap();
  }
  return libraryPromise;
}

async function fetchLibraryMap() {
  var map = {};
  if (!supabase) {
    return map;
  }
  var user = await getUser();
  if (!user) {
    return map;
  }
  loggedIn = true;
  try {
    var rows = await getLibrary();
    for (var i = 0; i < rows.length; i++) {
      map[rows[i].game_id] = rows[i].status;
    }
  } catch (error) {
    console.log(error);
  }
  return map;
}

// call this after the cards are shown. It colours the buttons of the games that are already saved.
export async function markSavedGames() {
  var map = await loadLibraryMap();
  var buttons = document.querySelectorAll('.save-button');
  for (var i = 0; i < buttons.length; i++) {
    var status = map[buttons[i].getAttribute('data-id')];
    buttons[i].classList.toggle('saved', Boolean(status));
    buttons[i].title = status ? 'In your library: ' + statusNames[status] : 'Add to library';
  }
}

function closeMenus() {
  var menus = document.querySelectorAll('.library-menu');
  for (var i = 0; i < menus.length; i++) {
    menus[i].remove();
  }
}

async function openMenu(button) {
  if (!supabase) {
    alert('The library is not set up yet (supabase keys are missing in the .env file).');
    return;
  }

  var map = await loadLibraryMap();
  if (!loggedIn) {
    // send the user to login and bring them back here afterwards
    var here = window.location.pathname.split('/').pop() + window.location.search;
    window.location.href = 'login.html?next=' + encodeURIComponent(here);
    return;
  }

  var id = button.getAttribute('data-id');
  var current = map[id];

  var html = '<p class="menu-title">Add to library</p>';
  var keys = Object.keys(statusNames);
  for (var i = 0; i < keys.length; i++) {
    var tick = (current == keys[i]) ? ' selected' : '';
    html += '<button class="menu-option' + tick + '" data-id="' + id + '" data-status="' + keys[i] + '">' + statusNames[keys[i]] + '</button>';
  }
  if (current) {
    html += '<button class="menu-option remove" data-id="' + id + '" data-status="remove">Remove from library</button>';
  }

  var menu = document.createElement('div');
  menu.className = 'library-menu';
  menu.innerHTML = html;
  button.parentElement.appendChild(menu);
}

async function chooseOption(option) {
  var id = option.getAttribute('data-id');
  var status = option.getAttribute('data-status');
  var map = await loadLibraryMap();

  try {
    if (status == 'remove') {
      await removeFromLibrary(id);
      delete map[id];
    } else {
      await saveToLibrary(knownGames[id], status);
      map[id] = status;
    }
  } catch (error) {
    console.log(error);
    alert('Something went wrong. Did you run the library.sql file in supabase?');
  }
  closeMenus();
  markSavedGames();
}

// one click listener for the whole page, so it also works for cards that are added later
document.addEventListener('click', function (event) {
  var option = event.target.closest('.menu-option');
  if (option) {
    chooseOption(option);
    return;
  }

  var button = event.target.closest('.save-button');
  var alreadyOpen = button ? button.parentElement.querySelector('.library-menu') : null;
  closeMenus();
  if (button && !alreadyOpen) {
    openMenu(button);
  }
});
