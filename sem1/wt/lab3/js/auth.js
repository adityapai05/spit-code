// Jayshree
// Login, signup and logout using supabase.

import { supabase } from './config.js';

// returns the logged in user, or null if nobody is logged in
export async function getUser() {
  if (!supabase) {
    return null;
  }
  var result = await supabase.auth.getUser();
  return result.data.user;
}

export async function signUp(email, password) {
  return await supabase.auth.signUp({ email: email, password: password });
}

export async function logIn(email, password) {
  return await supabase.auth.signInWithPassword({ email: email, password: password });
}

export async function logOut() {
  await supabase.auth.signOut();
}
