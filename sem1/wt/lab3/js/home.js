// Aditya
// the recommender box uses Yuvraj's recommend.js
// It handles the big search box and loads four sections of games from RAWG.

import { getGames } from './api.js';
import { makeCard, markSavedGames } from './card.js';
import { runSearch } from './recommend.js';
import { setupMenu } from './menu.js';

setupMenu();

// ----- the search box in the top part -----
var heroInput = document.getElementById('hero-input');

document.getElementById('hero-form').addEventListener('submit', function (event) {
  event.preventDefault();
  var text = heroInput.value.trim();
  if (text == '') {
    heroInput.focus();
    return;
  }
  runSearch(text);
});

// the example buttons put their text in the box and search
var examples = document.querySelectorAll('.example');
for (var e = 0; e < examples.length; e++) {
  examples[e].addEventListener('click', function (event) {
    heroInput.value = event.target.textContent;
    runSearch(heroInput.value);
  });
}

// ----- the four game sections -----

// turns a date into the format RAWG wants (2026-10-10)
function dateText(date) {
  return date.toISOString().slice(0, 10);
}

var today = new Date();
var threeMonthsAgo = new Date();
threeMonthsAgo.setDate(today.getDate() - 90);
var nextYear = new Date();
nextYear.setDate(today.getDate() + 365);
var tomorrow = new Date();
tomorrow.setDate(today.getDate() + 1);

// loads one section. "boxId" is the id of the div in index.html
async function loadSection(boxId, options) {
  var box = document.getElementById(boxId);
  options.pageSize = 4;
  try {
    var data = await getGames(options);
    var html = '';
    for (var i = 0; i < data.results.length; i++) {
      html = html + makeCard(data.results[i]);
    }
    box.innerHTML = html;
    markSavedGames();
  } catch (error) {
    console.log(error);
    box.innerHTML = '<p class="message">Could not load games. Check the RAWG key in the .env file.</p>';
  }
}

loadSection('popular-games', { ordering: '-added' });
loadSection('new-games', { dates: dateText(threeMonthsAgo) + ',' + dateText(today), ordering: '-added' });
loadSection('top-games', { metacritic: '85,100', ordering: '-metacritic' });
loadSection('upcoming-games', { dates: dateText(tomorrow) + ',' + dateText(nextYear), ordering: '-added' });
