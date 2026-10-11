// Vite config
// We use Vite only so that the .env values work and so that we can import the supabase package.
// Every html page has to be listed here so that "npm run build" includes it.
import { defineConfig } from 'vite';
import { resolve } from 'path';

export default defineConfig({
  build: {
    rollupOptions: {
      input: {
        home: resolve(__dirname, 'index.html'),
        games: resolve(__dirname, 'games.html'),
        game: resolve(__dirname, 'game.html'),
        library: resolve(__dirname, 'library.html'),
        login: resolve(__dirname, 'login.html'),
        about: resolve(__dirname, 'about.html'),
      },
    },
  },
});