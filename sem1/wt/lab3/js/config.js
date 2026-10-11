// Aditya
// This file reads the keys from the .env file and sets up supabase.

import { createClient } from '@supabase/supabase-js';

export const RAWG_KEY = import.meta.env.VITE_RAWG_API_KEY;
export const RAWG_URL = 'https://api.rawg.io/api';

export const GEMINI_KEY = import.meta.env.VITE_GEMINI_API_KEY;

var supabaseUrl = import.meta.env.VITE_SUPABASE_URL;
var supabaseKey = import.meta.env.VITE_SUPABASE_PUBLISHABLE_KEY;

// if the supabase keys are not filled in, supabase stays null and the library shows a message
export var supabase = null;
if (supabaseUrl && supabaseKey) {
  supabase = createClient(supabaseUrl, supabaseKey);
}
