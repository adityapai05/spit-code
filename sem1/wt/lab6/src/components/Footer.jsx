import { Link } from "react-router-dom";

function Footer() {
  return (
    <footer className="footer">
      <div className="container footer-inner">
        <div>
          <div className="logo">
            Monsoon<span>Co.</span>
          </div>
          <p>Stay dry. Move freely.</p>
        </div>
        <div className="footer-links">
          <Link to="/">Home</Link>
          <Link to="/products">Shop</Link>
          <Link to="/cart">Cart</Link>
        </div>
        <p className="footer-note">
          Cash on delivery across India.
        </p>
      </div>
    </footer>
  );
}

export default Footer;
