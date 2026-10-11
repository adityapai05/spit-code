// Aditya
// Runs on every page. It does two small things:
//  1. opens and closes the menu on phones
//  2. shows the Log in button, or the username and a logout icon when the user is logged in

import { getUser, logOut } from './auth.js';

export async function setupMenu() {
  // phone menu button
  var button = document.getElementById('menu-button');
  var nav = document.getElementById('main-nav');
  button.addEventListener('click', function () {
    nav.classList.toggle('open');
  });

  var user = await getUser();
  if (user) {
    // the username is the part of the email before the @ (adityapai1912@gmail.com -> adityapai1912)
    var username = user.email.split('@')[0];

    document.getElementById('user-letter').textContent = username.charAt(0).toUpperCase();
    document.getElementById('user-name').textContent = username;
    document.getElementById('user-chip').hidden = false;
    document.getElementById('login-link').hidden = true;

    var logoutButton = document.getElementById('logout-button');
    logoutButton.hidden = false;
    logoutButton.addEventListener('click', async function () {
      await logOut();
      window.location.href = 'index.html';
    });
  }
}