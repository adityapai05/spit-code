import { Link } from "react-router-dom";
import { formatPrice } from "../data/pricing.js";

function ProductCard({ product, addToCart }) {
  return (
    <article className="product-card">
      <Link to={"/products/" + product.id} className="card-image">
        <img src={product.image} alt={product.name} />
      </Link>
      <div className="card-body">
        <span className="category-tag">{product.category}</span>
        <h3>{product.name}</h3>
        <p className="muted">{product.shortDescription}</p>
        <p className="price">{formatPrice(product.price)}</p>
        <div className="card-actions">
          <Link to={"/products/" + product.id} className="btn btn-primary">
            View Details
          </Link>
        </div>
      </div>
    </article>
  );
}

export default ProductCard;
