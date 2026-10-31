import { Link, useNavigate } from "react-router-dom";
import CartItem from "../components/CartItem.jsx";
import {
  formatPrice,
  getTotals,
  FREE_DELIVERY_ABOVE,
} from "../data/pricing.js";

function Cart({ cart, setCart }) {
  const navigate = useNavigate();
  const { totalItems, subtotal, delivery, total } = getTotals(cart);

  function increaseQuantity(id) {
    setCart(
      cart.map((item) =>
        item.id === id ? { ...item, quantity: item.quantity + 1 } : item,
      ),
    );
  }

  function decreaseQuantity(id) {
    setCart(
      cart.map((item) =>
        item.id === id
          ? { ...item, quantity: Math.max(1, item.quantity - 1) }
          : item,
      ),
    );
  }

  function removeItem(id) {
    setCart(cart.filter((item) => item.id !== id));
  }

  function goToCheckout() {
    if (cart.length === 0) return; // block checkout for an empty cart
    navigate("/checkout");
  }

  if (cart.length === 0) {
    return (
      <div className="container section center-box">
        <div className="empty-art">0</div>
        <h1>Your cart is empty</h1>
        <p className="muted">
          Nothing here yet. Browse the collection and add something for the next
          downpour.
        </p>
        <Link to="/products" className="btn btn-primary">
          Browse products
        </Link>
      </div>
    );
  }

  return (
    <div className="container section">
      <h1 className="page-title">Your cart</h1>
      <div className="cart-layout">
        <div>
          {cart.map((item) => (
            <CartItem
              key={item.id}
              item={item}
              onIncrease={increaseQuantity}
              onDecrease={decreaseQuantity}
              onRemove={removeItem}
            />
          ))}
        </div>
        <aside className="summary">
          <h3>Order summary</h3>
          <div className="summary-row">
            <span>Items</span>
            <span>{totalItems}</span>
          </div>
          <div className="summary-row">
            <span>Subtotal</span>
            <span>{formatPrice(subtotal)}</span>
          </div>
          <div className="summary-row">
            <span>Delivery</span>
            <span>{delivery === 0 ? "Free" : formatPrice(delivery)}</span>
          </div>
          {delivery > 0 && (
            <p className="muted small">
              Free delivery on orders above {formatPrice(FREE_DELIVERY_ABOVE)}
            </p>
          )}
          <div className="summary-row total">
            <span>Total</span>
            <span>{formatPrice(total)}</span>
          </div>
          <button className="btn btn-primary full" onClick={goToCheckout}>
            Proceed to Checkout
          </button>
          <Link to="/products" className="btn btn-outline full">
            Continue Shopping
          </Link>
        </aside>
      </div>
    </div>
  );
}

export default Cart;
