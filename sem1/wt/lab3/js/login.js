// Jayshree
// The login page. One form with two modes: "login" and "signup".
// The link at the bottom changes the mode (New to QUEST? Create an account).

import { logIn, signUp, getUser } from './auth.js';
import { supabase } from './config.js';
import { setupMenu } from './menu.js';

setupMenu();

var form = document.getElementById('login-form');
var title = document.getElementById('form-title');
var subtitle = document.getElementById('form-subtitle');
var emailBox = document.getElementById('email');
var passwordBox = document.getElementById('password');
var confirmRow = document.getElementById('confirm-row');
var confirmBox = document.getElementById('confirm');
var submitButton = document.getElementById('submit-button');
var switchText = document.getElementById('switch-text');
var switchLink = document.getElementById('switch-link');
var message = document.getElementById('login-message');

var mode = 'login';

// after login we go back to the page the user came from (login.html?next=game.html?id=5)
// we only allow our own pages here, so nobody can send the user to another website
var params = new URLSearchParams(window.location.search);
var nextPage = params.get('next');
if (nextPage == null || !/^[a-z]+\.html(\?[\w=&.-]*)?$/i.test(nextPage)) {
  nextPage = 'index.html';
}

function setMode(newMode) {
  mode = newMode;
  message.textContent = '';
  if (mode == 'login') {
    title.textContent = 'Welcome back';
    subtitle.textContent = 'Log in to open your library.';
    confirmRow.hidden = true;
    confirmBox.required = false;
    submitButton.textContent = 'Log in';
    switchText.textContent = 'New to QUEST? ';
    switchLink.textContent = 'Create an account';
    passwordBox.autocomplete = 'current-password';
  } else {
    title.textContent = 'Create your account';
    subtitle.textContent = 'Sign up to save games to your library.';
    confirmRow.hidden = false;
    confirmBox.required = true;
    submitButton.textContent = 'Create account';
    switchText.textContent = 'Already have an account? ';
    switchLink.textContent = 'Log in';
    passwordBox.autocomplete = 'new-password';
  }
}

switchLink.addEventListener('click', function (event) {
  event.preventDefault();
  setMode(mode == 'login' ? 'signup' : 'login');
});

// the "Create an account" links on other pages open this page in signup mode
if (params.get('mode') == 'signup') {
  setMode('signup');
} else {
  setMode('login');
}

if (!supabase) {
  message.textContent = 'Login is not set up yet (supabase keys are missing in the .env file).';
}

// if the user is already logged in we send them away from the login page
async function checkUser() {
  var user = await getUser();
  if (user) {
    window.location.href = nextPage;
  }
}
checkUser();

form.addEventListener('submit', async function (event) {
  event.preventDefault();
  if (!supabase) {
    return;
  }

  if (mode == 'login') {
    message.textContent = 'Please wait...';
    var result = await logIn(emailBox.value, passwordBox.value);
    if (result.error) {
      message.textContent = result.error.message;
    } else {
      window.location.href = nextPage;
    }
    return;
  }

  // signup
  if (passwordBox.value.length < 6) {
    message.textContent = 'The password must have at least 6 characters.';
    return;
  }
  if (passwordBox.value != confirmBox.value) {
    message.textContent = 'The two passwords are not the same.';
    return;
  }

  message.textContent = 'Please wait...';
  var created = await signUp(emailBox.value, passwordBox.value);
  if (created.error) {
    message.textContent = created.error.message;
  } else if (created.data.session) {
    window.location.href = nextPage;
  } else {
    // happens when email confirmation is turned on in supabase
    message.textContent = 'Account created! Check your email to confirm it, then log in.';
  }
});
