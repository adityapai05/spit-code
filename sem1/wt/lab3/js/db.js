// Jayshree
// The library functions. They save games in the "library" table in supabase.
// Every game has a status: 'want-to-play', 'playing' or 'completed'.

import { supabase } from './config.js';

// the names we show on the screen for each status
export var statusNames = {
  'want-to-play': 'Want to Play',
  'playing': 'Playing',
  'completed': 'Completed',
};

// get all the games in the library of the logged in user
export async function getLibrary() {
  var result = await supabase
    .from('library')
    .select('*')
    .order('created_at', { ascending: false });
  if (result.error) {
    throw result.error;
  }
  return result.data;
}

// returns the status of one game ('playing' etc.) or null if it is not in the library
export async function getStatus(gameId) {
  var result = await supabase.from('library').select('status').eq('game_id', gameId);
  if (result.error) {
    throw result.error;
  }
  if (result.data.length == 0) {
    return null;
  }
  return result.data[0].status;
}

// add a game, or change its status if it is already there
export async function saveToLibrary(game, status) {
  var result = await supabase.from('library').upsert(
    {
      game_id: game.id,
      game_name: game.name,
      game_image: game.background_image,
      status: status,
    },
    { onConflict: 'user_id,game_id' }
  );
  if (result.error) {
    throw result.error;
  }
}

export async function removeFromLibrary(gameId) {
  var result = await supabase.from('library').delete().eq('game_id', gameId);
  if (result.error) {
    throw result.error;
  }
}
