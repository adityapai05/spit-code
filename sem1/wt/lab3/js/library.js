// Jayshree
// The library page. It shows the saved games of the logged in user in three lists:
// Want to Play, Playing and Completed.

import { getUser } from './auth.js';
import { supabase } from './config.js';
import { getLibrary, saveToLibrary, removeFromLibrary, statusNames } from './db.js';
import { smallImage } from './card.js';
import { setupMenu } from './menu.js';

setupMenu();

var list = document.getElementById('library-list');
var tabs = document.getElementById('library-tabs');

// shows a centered box with an icon, a title, a sentence and some buttons
// (used when the user is not logged in, or when a list is empty)
function showBox(title, text, buttons) {
  var html = '';
  html += '<div class="empty-state">';
  html += '  <div class="empty-icon">';
  html += '    <svg viewBox="0 0 24 24" width="28" height="28"><path d="M6 3h12a1 1 0 0 1 1 1v17l-7-4-7 4V4a1 1 0 0 1 1-1z"/></svg>';
  html += '  </div>';
  html += '  <h2>' + title + '</h2>';
  html += '  <p>' + text + '</p>';
  html += '  <div class="empty-buttons">' + buttons + '</div>';
  html += '</div>';
  list.innerHTML = html;
}

var allGames = [];            // all the games of the user
var currentStatus = 'want-to-play';   // the tab that is open

// shows the games of the open tab
function showGames() {
  // update the tab buttons and the counts
  var buttons = document.querySelectorAll('.tab');
  for (var b = 0; b < buttons.length; b++) {
    var name = buttons[b].getAttribute('data-status');
    var count = allGames.filter(function (g) { return g.status == this; }, name).length;
    buttons[b].textContent = statusNames[name] + ' (' + count + ')';
    buttons[b].classList.toggle('active', name == currentStatus);
  }

  var games = allGames.filter(function (g) {
    return g.status == currentStatus;
  });

  if (games.length == 0) {
    showBox(
      'Nothing in ' + statusNames[currentStatus] + ' yet',
      'Find a game you like and add it to this list.',
      '<a href="index.html" class="button">Get recommendations</a><a href="games.html" class="button outline">Browse games</a>'
    );
    return;
  }

  var html = '';
  for (var i = 0; i < games.length; i++) {
    var g = games[i];
    html += '<div class="card">';
    html += '  <div class="card-image"><a href="game.html?id=' + g.game_id + '"><img src="' + smallImage(g.game_image) + '" alt="' + g.game_name + '" loading="lazy"></a></div>';
    html += '  <div class="card-body">';
    html += '    <h3><a href="game.html?id=' + g.game_id + '">' + g.game_name + '</a></h3>';
    html += '    <select class="status-select" data-id="' + g.game_id + '">';
    html += '      <option value="want-to-play"' + (g.status == 'want-to-play' ? ' selected' : '') + '>Want to Play</option>';
    html += '      <option value="playing"' + (g.status == 'playing' ? ' selected' : '') + '>Playing</option>';
    html += '      <option value="completed"' + (g.status == 'completed' ? ' selected' : '') + '>Completed</option>';
    html += '    </select>';
    html += '    <button class="button outline small remove-button" data-id="' + g.game_id + '">Remove</button>';
    html += '  </div>';
    html += '</div>';
  }
  list.innerHTML = html;

  // when the status dropdown of a card changes
  var selects = document.querySelectorAll('.status-select');
  for (var s = 0; s < selects.length; s++) {
    selects[s].addEventListener('change', async function (event) {
      var id = event.target.getAttribute('data-id');
      var game = allGames.find(function (x) { return x.game_id == id; });
      await saveToLibrary({ id: game.game_id, name: game.game_name, background_image: game.game_image }, event.target.value);
      game.status = event.target.value;
      showGames();
    });
  }

  // when a remove button is clicked
  var removes = document.querySelectorAll('.remove-button');
  for (var r = 0; r < removes.length; r++) {
    removes[r].addEventListener('click', async function (event) {
      var id = event.target.getAttribute('data-id');
      await removeFromLibrary(id);
      allGames = allGames.filter(function (x) { return x.game_id != id; });
      showGames();
    });
  }
}

async function startPage() {
  if (!supabase) {
    tabs.style.display = 'none';
    showBox('Library is not set up', 'The supabase keys are missing in the .env file.', '');
    return;
  }

  var user = await getUser();
  if (!user) {
    tabs.style.display = 'none';
    showBox(
      'Log in to see your library',
      'Save games as Want to Play, Playing or Completed and find them here.',
      '<a href="login.html?next=library.html" class="button">Log in</a><a href="login.html?mode=signup&next=library.html" class="button outline">Create an account</a>'
    );
    return;
  }

  try {
    allGames = await getLibrary();
  } catch (error) {
    console.log(error);
    tabs.style.display = 'none';
    showBox('Could not load the library', 'Did you run the library.sql file in supabase?', '');
    return;
  }

  // click on a tab
  var buttons = document.querySelectorAll('.tab');
  for (var i = 0; i < buttons.length; i++) {
    buttons[i].addEventListener('click', function (event) {
      currentStatus = event.target.getAttribute('data-status');
      showGames();
    });
  }

  showGames();
}

startPage();