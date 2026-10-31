import { Link } from "react-router-dom";
import ProductCard from "../components/ProductCard.jsx";
import products, { categories } from "../data/products.js";

const categoryNotes = {
  Rainwear: "Jackets and ponchos",
  Umbrellas: "Compact, automatic, windproof",
  "Waterproof Gear": "Backpacks and pouches",
  Footwear: "Boots and waterproof shoes",
  Accessories: "Shoe covers and towels",
};

function Home({ addToCart }) {
  const featuredProducts = products.slice(0, 4);

  return (
    <div>
      <section className="hero">
        <div className="container hero-inner">
          <div className="hero-text">
            <p className="hero-brand">
              Stay dry. Move freely.
            </p>
            <h1>Rain Outside. Adventure Within.</h1>
            <p>
              Discover thoughtfully selected essentials that keep you
              comfortable, protected, and ready for every monsoon day.
            </p>
            <Link to="/products" className="btn btn-accent">
              Shop the Collection
            </Link>
          </div>
          <img
            className="hero-image"
            src="/images/drift-umbrella.svg"
            alt="Monsoon Co. umbrella"
          />
        </div>
      </section>

      <section className="section container">
        <div className="section-head">
          <h2>Featured picks</h2>
          <Link to="/products" className="text-link">
            See all products
          </Link>
        </div>
        <div className="product-grid">
          {featuredProducts.map((product) => (
            <ProductCard
              key={product.id}
              product={product}
              addToCart={addToCart}
            />
          ))}
        </div>
      </section>

      <section className="section container">
        <h2>Shop by category</h2>
        <div className="category-row">
          {categories.map((name) => (
            <Link to="/products" className="category-item" key={name}>
              <h3>{name}</h3>
              <p>{categoryNotes[name]}</p>
            </Link>
          ))}
        </div>
      </section>

      <section className="promo">
        <div className="container promo-inner">
          <h2>Free delivery on orders above ₹999</h2>
          <p>
            Pay when it arrives. Cash on delivery is available everywhere we
            ship.
          </p>
          <Link to="/products" className="btn btn-accent">
            Start shopping
          </Link>
        </div>
      </section>
    </div>
  );
}

export default Home;
