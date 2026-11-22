import { defineConfig } from "vite";
import react from "@vitejs/plugin-react";

// the proxy forwards /books calls to the backend so we dont get cors errors
export default defineConfig({
  plugins: [react()],
  server: {
    port: 5173,
    proxy: {
      "/books": {
        target: "http://localhost:3000",
        changeOrigin: true,
      },
    },
  },
});
