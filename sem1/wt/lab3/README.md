# QUEST - Game Discovery Website

Lab 3 - Website Development

Team: Aditya, Yuvraj and Jayshree

QUEST helps you decide what game to play next. On the home page you type what you feel like playing in your own
words (for example "a short emotional story game" or "something like Hollow Knight"). Gemini turns the sentence
into genres and tags, RAWG gives real matching games, and you can save games to your own library
(Want to Play, Playing, Completed).

## Pages

| Page         | File         | Script        | What it does                                                         |
| ------------ | ------------ | ------------- | -------------------------------------------------------------------- |
| Home         | index.html   | js/home.js    | Explains the project, the recommender box and 4 game sections        |
| Browse Games | games.html   | js/games.js   | Search, genre, platform, rating, playtime filters, sorting and pages |
| Game details | game.html    | js/game.js    | Details, screenshots, store links and the library box                |
| My Library   | library.html | js/library.js | Saved games in three tabs                                            |
| Login        | login.html   | js/login.js   | Login and create account                                             |
| About Quest        | about.html   | js/about.js   | About the project and the team                                       |

## Who did what

**Aditya**

- Project setup, Vite config and `.env` handling (`js/config.js`, `vite.config.js`)
- RAWG API functions (`js/api.js`)
- Home page and its four sections (`index.html`, `js/home.js`, `css/home.css`)
- Game details page with screenshots and store links (`game.html`, `js/game.js`, `css/game.css`)
- Header (username and logout icon), footer and phone menu (`js/menu.js`, `css/style.css`)

**Yuvraj**

- Gemini part (`js/gemini.js`)
- The recommender on the home page and the "why this game" lines (`js/recommend.js`)
- Browse page with six filters (`games.html`, `js/games.js`, `css/games.css`)
- Game cards and the add to library button on the cards (`js/card.js`, card part of `css/style.css`)

**Jayshree**

- Supabase setup and the library table (`database/library.sql`, `js/db.js`)
- Login and create account (`login.html`, `js/login.js`, `js/auth.js`, `css/login.css`)
- My Library page (`library.html`, `js/library.js`, `css/library.css`)
- Library box on the game page (the bottom part of `js/game.js`)
- About page (`about.html`, `css/about.css`)

## How the recommender works

1. The user types a sentence in the box on the home page.
2. `gemini.js` sends it to Gemini and asks for JSON with genres, tags and (if the user said "like X") a game name.
   Gemini is only allowed to pick from our own lists, and we check the answer again in `cleanAnswer()`.
3. If a game name was given, `recommend.js` looks it up in RAWG and uses that game's genres and tags.
4. `recommend.js` asks RAWG for games with those genres and tags. If nothing comes back it tries with fewer filters.
5. Each card gets a "Matches: ..." line made from the genres and tags RAWG returned for that game.
6. If Gemini does not work (no key, no internet, quota over), the page searches RAWG with the user's words instead, so it never breaks.

## How to run

You need Node.js installed.

1. Open a terminal in this folder and run `npm install`
2. Copy `.env.example` to a new file called `.env` and fill in the values:
   - `VITE_RAWG_API_KEY`: free key from https://rawg.io/apidocs
   - `VITE_GEMINI_API_KEY`: free key from https://aistudio.google.com/apikey
   - `VITE_SUPABASE_URL` and `VITE_SUPABASE_PUBLISHABLE_KEY`: in Supabase, Project Settings, API
3. In Supabase open the SQL Editor, paste everything from `database/library.sql` and press Run. This makes the library table.
5. Run `npm run dev` and open the link shown in the terminal (usually http://localhost:5173)

If you change `.env`, stop the server and run `npm run dev` again.

The site still works without the Gemini key (plain RAWG search) and without the Supabase values (only login and library are disabled).

## Technologies

- HTML, CSS, JavaScript
- RAWG API (https://rawg.io) for game data
- Google Gemini API to understand the sentence
- Supabase for login and the library table
- Vite to run the project and read the `.env` file
