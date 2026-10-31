import { Link } from "react-router-dom";
import { formatPrice } from "../data/pricing.js";

function CartItem({ item, onIncrease, onDecrease, onRemove }) {
  return (
    <div className="cart-item">
      <Link to={"/products/" + item.id}>
        <img src={item.image} alt={item.name} />
      </Link>
      <div className="cart-item-info">
        <h3>{item.name}</h3>
        <p className="muted">{formatPrice(item.price)} each</p>
        <div className="qty-box">
          <button
            onClick={() => onDecrease(item.id)}
            disabled={item.quantity === 1}
            aria-label="Decrease quantity"
          >
            -
          </button>
          <span>{item.quantity}</span>
          <button
            onClick={() => onIncrease(item.id)}
            aria-label="Increase quantity"
          >
            +
          </button>
        </div>
      </div>
      <div className="cart-item-side">
        <strong>{formatPrice(item.price * item.quantity)}</strong>
        <button className="link-btn" onClick={() => onRemove(item.id)}>
          Remove
        </button>
      </div>
    </div>
  );
}

export default CartItem;
