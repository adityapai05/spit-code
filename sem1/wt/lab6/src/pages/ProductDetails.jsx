import { useState } from "react";
import { Link, useParams } from "react-router-dom";
import products from "../data/products.js";
import { formatPrice } from "../data/pricing.js";

function ProductDetails({ addToCart }) {
  const { productId } = useParams();
  const [quantity, setQuantity] = useState(1);
  const [message, setMessage] = useState("");

  const product = products.find((item) => item.id === Number(productId));

  if (!product) {
    return (
      <div className="container section center-box">
        <h1>Product not found</h1>
        <p className="muted">
          We could not find a product with ID "{productId}".
        </p>
        <Link to="/products" className="btn btn-primary">
          Back to shop
        </Link>
      </div>
    );
  }

  function handleAdd() {
    addToCart(product, quantity);
    setMessage(quantity + " added to your cart");
  }

  return (
    <div className="container section">
      <Link to="/products" className="text-link">
        &larr; Back to Products
      </Link>
      <div className="details">
        <img className="details-image" src={product.image} alt={product.name} />
        <div>
          <span className="category-tag">{product.category}</span>
          <h1>{product.name}</h1>
          <p className="details-price">{formatPrice(product.price)}</p>
          <p>{product.description}</p>
          <h3>Features</h3>
          <ul className="feature-list">
            {product.features.map((feature) => (
              <li key={feature}>{feature}</li>
            ))}
          </ul>
          <div className="buy-row">
            <div className="qty-box">
              <button
                onClick={() => setQuantity(Math.max(1, quantity - 1))}
                aria-label="Decrease quantity"
              >
                -
              </button>
              <span>{quantity}</span>
              <button
                onClick={() => setQuantity(quantity + 1)}
                aria-label="Increase quantity"
              >
                +
              </button>
            </div>
            <button className="btn btn-primary" onClick={handleAdd}>
              Add to Cart
            </button>
          </div>
          {message && (
            <p className="success-text">
              {message}. <Link to="/cart">View cart</Link>
            </p>
          )}
        </div>
      </div>
    </div>
  );
}

export default ProductDetails;
