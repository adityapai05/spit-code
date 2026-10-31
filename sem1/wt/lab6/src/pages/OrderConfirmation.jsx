import { Link } from "react-router-dom";
import { formatPrice } from "../data/pricing.js";

function OrderConfirmation({ order }) {
  if (!order) {
    return (
      <div className="container section center-box">
        <h1>No recent order found</h1>
        <p className="muted">
          Place an order first and your confirmation will appear here.
        </p>
        <Link to="/" className="btn btn-primary">
          Go to homepage
        </Link>
      </div>
    );
  }

  const { customer } = order;

  return (
    <div className="container section">
      <div className="confirm-box">
        <div className="tick">&#10003;</div>
        <h1>Thank you, {customer.fullName}. Your order is confirmed.</h1>
        <p className="muted">
          Order ID: <strong>{order.orderId}</strong>
        </p>

        <div className="confirm-grid">
          <div>
            <h3>Delivery address</h3>
            <p>
              {customer.address}
              <br />
              {customer.city}, {customer.state} {customer.pincode}
              <br />
              {customer.mobile}
            </p>
            <h3>Payment method</h3>
            <p>{order.paymentMethod}</p>
          </div>
          <div>
            <h3>Items</h3>
            {order.items.map((item) => (
              <div className="summary-row" key={item.id}>
                <span>
                  {item.name} x {item.quantity}
                </span>
                <span>{formatPrice(item.price * item.quantity)}</span>
              </div>
            ))}
            <div className="summary-row">
              <span>Subtotal</span>
              <span>{formatPrice(order.subtotal)}</span>
            </div>
            <div className="summary-row">
              <span>Delivery</span>
              <span>
                {order.delivery === 0 ? "Free" : formatPrice(order.delivery)}
              </span>
            </div>
            <div className="summary-row total">
              <span>Final amount</span>
              <span>{formatPrice(order.total)}</span>
            </div>
          </div>
        </div>
        <Link to="/products" className="btn btn-primary">
          Continue Shopping
        </Link>
      </div>
    </div>
  );
}

export default OrderConfirmation;
