import { useState } from "react";
import { Link } from "react-router-dom";

function Header({ cart }) {
  const [menuOpen, setMenuOpen] = useState(false);
  const totalItems = cart.reduce((sum, item) => sum + item.quantity, 0);

  function closeMenu() {
    setMenuOpen(false);
  }

  return (
    <header className="header">
      <div className="container header-inner">
        <Link to="/" className="logo" onClick={closeMenu}>
          Monsoon<span>Co.</span>
        </Link>
        <button
          className="menu-btn"
          onClick={() => setMenuOpen(!menuOpen)}
          aria-label="Toggle menu"
        >
          {menuOpen ? "Close" : "Menu"}
        </button>
        <nav className={menuOpen ? "nav open" : "nav"}>
          <Link to="/" onClick={closeMenu}>
            Home
          </Link>
          <Link to="/products" onClick={closeMenu}>
            Shop
          </Link>
          <Link to="/cart" onClick={closeMenu}>
            Cart <span className="badge">{totalItems}</span>
          </Link>
        </nav>
      </div>
    </header>
  );
}

export default Header;
