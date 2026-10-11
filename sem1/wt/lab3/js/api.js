//  Aditya
// These functions get the data from the RAWG api.

import { RAWG_KEY, RAWG_URL } from './config.js';

// get a list of games.
// "options" can have: search, genre, platform, tags, ordering, page, pageSize, dates, metacritic
export async function getGames(options) {
  var params = new URLSearchParams();
  params.set('key', RAWG_KEY);
  params.set('page_size', options.pageSize || 12);

  if (options.search) {
    params.set('search', options.search);
  }
  if (options.genre) {
    params.set('genres', options.genre);
  }
  if (options.platform) {
    params.set('parent_platforms', options.platform);
  }
  if (options.tags) {
    params.set('tags', options.tags);
  }
  if (options.ordering) {
    params.set('ordering', options.ordering);
  }
  if (options.page) {
    params.set('page', options.page);
  }
  if (options.dates) {
    params.set('dates', options.dates);
  }
  if (options.metacritic) {
    params.set('metacritic', options.metacritic);
  }

  var response = await fetch(RAWG_URL + '/games?' + params.toString());
  if (!response.ok) {
    throw new Error('RAWG gave an error: ' + response.status);
  }
  return await response.json();
}

// get all the details of one game
export async function getGameDetails(id) {
  var response = await fetch(RAWG_URL + '/games/' + id + '?key=' + RAWG_KEY);
  if (!response.ok) {
    throw new Error('RAWG gave an error: ' + response.status);
  }
  return await response.json();
}

// get the screenshots of one game (returns a list, or an empty list if it fails)
export async function getScreenshots(id) {
  try {
    var response = await fetch(RAWG_URL + '/games/' + id + '/screenshots?key=' + RAWG_KEY);
    if (!response.ok) {
      return [];
    }
    var data = await response.json();
    return data.results;
  } catch (error) {
    return [];
  }
}

// get the store links of one game (Steam, Epic etc).
// RAWG only gives the links on some plans, so if this fails we return an empty list and the page still works.
export async function getStoreLinks(id) {
  try {
    var response = await fetch(RAWG_URL + '/games/' + id + '/stores?key=' + RAWG_KEY);
    if (!response.ok) {
      return [];
    }
    var data = await response.json();
    return data.results;
  } catch (error) {
    return [];
  }
}
