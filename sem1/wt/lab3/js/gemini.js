// Yuvraj
// Sends the user's sentence to Gemini and gets back simple filters (genres and tags) that RAWG understands.
// Gemini does NOT choose the games. It only turns the sentence into filters, and RAWG gives the real games.

import { GEMINI_KEY } from './config.js';

// Gemini is only allowed to pick from these lists, because RAWG understands these words
export var allowedGenres = [
  'action', 'indie', 'adventure', 'role-playing-games-rpg', 'strategy', 'shooter', 'casual',
  'simulation', 'puzzle', 'arcade', 'platformer', 'racing', 'sports', 'fighting', 'family',
];

export var allowedTags = [
  'singleplayer', 'multiplayer', 'co-op', 'story-rich', 'atmospheric', 'open-world', 'horror',
  'relaxing', 'cute', 'funny', 'difficult', 'exploration', 'survival', 'stealth', 'fantasy',
  'sci-fi', 'emotional', 'fast-paced', 'turn-based', 'roguelike', 'pixel-graphics', 'first-person',
  'third-person', 'mystery', 'great-soundtrack', 'short',
];

// we try the main model first and the backup model if it fails
var models = ['gemini-3.5-flash-lite', 'gemini-3.1-flash-lite'];

function makePrompt(text) {
  return (
    'You help people find video games.\n' +
    'Read the request and reply with JSON only, in this format:\n' +
    '{"genres": [], "tags": [], "similarTo": "", "summary": ""}\n\n' +
    'Rules:\n' +
    '- genres: at most 2, only from this list: ' + allowedGenres.join(', ') + '\n' +
    '- tags: at most 3, only from this list: ' + allowedTags.join(', ') + '\n' +
    '- similarTo: the game name if the person says "like <game>", otherwise an empty string\n' +
    '- summary: one friendly sentence (under 20 words) saying what the person wants\n\n' +
    'Request: ' + text
  );
}

// returns {genres, tags, similarTo, summary} or null if Gemini did not work
export async function understandRequest(text) {
  if (!GEMINI_KEY) {
    return null;
  }

  for (var i = 0; i < models.length; i++) {
    try {
      var url =
        'https://generativelanguage.googleapis.com/v1beta/models/' + models[i] +
        ':generateContent?key=' + GEMINI_KEY;

      var response = await fetch(url, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({
          contents: [{ parts: [{ text: makePrompt(text) }] }],
          generationConfig: {
            responseMimeType: 'application/json',
            temperature: 0.2,
            maxOutputTokens: 2048,
          },
        }),
      });
      if (!response.ok) {
        throw new Error('Gemini error ' + response.status);
      }

      var data = await response.json();
      var answerText = data.candidates[0].content.parts[0].text;
      return cleanAnswer(JSON.parse(answerText));
    } catch (error) {
      console.log('Gemini model ' + models[i] + ' failed:', error);
    }
  }
  return null;
}

// make sure Gemini only used words from our lists
function cleanAnswer(answer) {
  var genres = [];
  var tags = [];

  if (Array.isArray(answer.genres)) {
    for (var i = 0; i < answer.genres.length; i++) {
      if (allowedGenres.includes(answer.genres[i]) && genres.length < 2) {
        genres.push(answer.genres[i]);
      }
    }
  }
  if (Array.isArray(answer.tags)) {
    for (var j = 0; j < answer.tags.length; j++) {
      if (allowedTags.includes(answer.tags[j]) && tags.length < 3) {
        tags.push(answer.tags[j]);
      }
    }
  }

  return {
    genres: genres,
    tags: tags,
    similarTo: typeof answer.similarTo == 'string' ? answer.similarTo.slice(0, 80) : '',
    summary: typeof answer.summary == 'string' ? answer.summary.slice(0, 200) : '',
  };
}
