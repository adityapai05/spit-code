// Yuvraj
// The browse page: search, genre, platform, rating, playtime, sorting and next/previous page buttons.

import { getGames } from './api.js';
import { makeCard, markSavedGames } from './card.js';
import { setupMenu } from './menu.js';

setupMenu();

var searchBox = document.getElementById('search');
var genreBox = document.getElementById('genre');
var platformBox = document.getElementById('platform');
var ratingBox = document.getElementById('rating');
var playtimeBox = document.getElementById('playtime');
var sortBox = document.getElementById('sort');
var form = document.getElementById('filter-form');
var resetButton = document.getElementById('reset-button');
var list = document.getElementById('game-list');
var info = document.getElementById('result-info');
var prevButton = document.getElementById('prev');
var nextButton = document.getElementById('next');
var pageText = document.getElementById('page-number');

var page = 1;

// the links on the home page send the genre or sorting in the url (games.html?genre=action)
var params = new URLSearchParams(window.location.search);
if (params.get('genre')) {
  genreBox.value = params.get('genre');
}
if (params.get('sort')) {
  sortBox.value = params.get('sort');
}

async function loadGames() {
  list.innerHTML = '<p class="message">Loading...</p>';

  // RAWG cannot filter by star rating or playtime, so for those two we filter the games ourselves.
  // We ask for more games per page (40) so that some are left after filtering.
  var filterOurselves = (ratingBox.value != '' || playtimeBox.value != '');

  try {
    var data = await getGames({
      search: searchBox.value,
      genre: genreBox.value,
      platform: platformBox.value,
      ordering: sortBox.value,
      page: page,
      pageSize: filterOurselves ? 40 : 12,
    });

    var games = data.results;

    // rating filter, for example "4" means 4 stars or more
    if (ratingBox.value != '') {
      games = games.filter(function (g) {
        return g.rating >= Number(ratingBox.value);
      });
    }

    // playtime filter, for example "5-15" means between 5 and 15 hours
    if (playtimeBox.value != '') {
      var range = playtimeBox.value.split('-');
      games = games.filter(function (g) {
        return g.playtime >= Number(range[0]) && g.playtime <= Number(range[1]);
      });
    }

    if (games.length == 0) {
      list.innerHTML = '<p class="message">No games found. Try changing the filters.</p>';
      info.textContent = '';
    } else {
      var html = '';
      for (var i = 0; i < games.length; i++) {
        html = html + makeCard(games[i]);
      }
      list.innerHTML = html;
      markSavedGames();

      if (filterOurselves) {
        info.textContent = games.length + ' of ' + data.results.length + ' games on this page match your filters';
      } else {
        info.textContent = data.count.toLocaleString() + ' games found';
      }
    }

    // the buttons are disabled when there is no previous or next page
    prevButton.disabled = (page == 1);
    nextButton.disabled = (data.next == null);
    pageText.textContent = 'Page ' + page;
  } catch (error) {
    console.log(error);
    list.innerHTML = '<p class="message">Sorry, could not load the games. Check the RAWG key in the .env file.</p>';
  }
}

// when the user searches or changes a filter we go back to page 1
function startAgain() {
  page = 1;
  loadGames();
}

form.addEventListener('submit', function (event) {
  event.preventDefault();
  startAgain();
});

var boxes = [genreBox, platformBox, ratingBox, playtimeBox, sortBox];
for (var i = 0; i < boxes.length; i++) {
  boxes[i].addEventListener('change', startAgain);
}

resetButton.addEventListener('click', function () {
  form.reset();
  startAgain();
});

prevButton.addEventListener('click', function () {
  page = page - 1;
  loadGames();
  window.scrollTo(0, 0);
});
nextButton.addEventListener('click', function () {
  page = page + 1;
  loadGames();
  window.scrollTo(0, 0);
});

loadGames();
