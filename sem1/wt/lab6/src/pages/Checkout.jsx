import { useState } from "react";
import { Link, useNavigate } from "react-router-dom";
import { formatPrice, getTotals } from "../data/pricing.js";

const fields = [
  { name: "fullName", label: "Full name", type: "text" },
  { name: "email", label: "Email address", type: "email" },
  { name: "mobile", label: "Mobile number", type: "tel" },
  { name: "address", label: "House number and street", type: "text" },
  { name: "city", label: "City", type: "text" },
  { name: "state", label: "State", type: "text" },
  { name: "pincode", label: "PIN code", type: "text" },
];

function Checkout({ cart, setCart, setOrder }) {
  const navigate = useNavigate();
  const [formData, setFormData] = useState({
    fullName: "",
    email: "",
    mobile: "",
    address: "",
    city: "",
    state: "",
    pincode: "",
  });
  const [errors, setErrors] = useState({});
  const { subtotal, delivery, total } = getTotals(cart);

  function handleChange(event) {
    setFormData({ ...formData, [event.target.name]: event.target.value });
  }

  // Returns an object with one error message per invalid field
  function validate() {
    const newErrors = {};
    fields.forEach((field) => {
      if (formData[field.name].trim() === "") {
        newErrors[field.name] = field.label + " is required";
      }
    });
    if (!newErrors.email && !/^\S+@\S+\.\S+$/.test(formData.email.trim())) {
      newErrors.email = "Enter a valid email like name@example.com";
    }
    if (!newErrors.mobile && !/^\d{10}$/.test(formData.mobile.trim())) {
      newErrors.mobile = "Mobile number must be exactly 10 digits";
    }
    if (!newErrors.pincode && !/^\d{6}$/.test(formData.pincode.trim())) {
      newErrors.pincode = "PIN code must be exactly 6 digits";
    }
    return newErrors;
  }

  function handleSubmit(event) {
    event.preventDefault();
    const newErrors = validate();
    setErrors(newErrors);
    if (Object.keys(newErrors).length > 0) return; // stop here, cart is NOT cleared

    const order = {
      orderId: "MON" + Date.now().toString().slice(-8),
      customer: formData,
      items: cart,
      subtotal: subtotal,
      delivery: delivery,
      total: total,
      paymentMethod: "Cash on Delivery",
    };
    setOrder(order);
    setCart([]);
    navigate("/order-confirmation");
  }

  if (cart.length === 0) {
    return (
      <div className="container section center-box">
        <h1>Nothing to check out</h1>
        <p className="muted">Add a product to your cart first.</p>
        <Link to="/products" className="btn btn-primary">
          Browse products
        </Link>
      </div>
    );
  }

  return (
    <div className="container section">
      <h1 className="page-title">Checkout</h1>
      <div className="cart-layout">
        <form className="checkout-form" onSubmit={handleSubmit} noValidate>
          <h3>Delivery details</h3>
          <div className="form-grid">
            {fields.map((field) => (
              <label
                key={field.name}
                className={field.name === "address" ? "wide" : ""}
              >
                {field.label}
                <input
                  type={field.type}
                  name={field.name}
                  value={formData[field.name]}
                  onChange={handleChange}
                  className={errors[field.name] ? "input-error" : ""}
                />
                {errors[field.name] && (
                  <span className="error-text">{errors[field.name]}</span>
                )}
              </label>
            ))}
          </div>
          <h3>Payment method</h3>
          <label className="payment-option">
            <input type="radio" name="payment" checked readOnly />
            <span>Cash on Delivery (pay when your order arrives)</span>
          </label>
          <button type="submit" className="btn btn-primary full">
            Place order
          </button>
        </form>

        <aside className="summary">
          <h3>Your order</h3>
          {cart.map((item) => (
            <div className="summary-row" key={item.id}>
              <span>
                {item.name} x {item.quantity}
              </span>
              <span>{formatPrice(item.price * item.quantity)}</span>
            </div>
          ))}
          <div className="summary-row">
            <span>Subtotal</span>
            <span>{formatPrice(subtotal)}</span>
          </div>
          <div className="summary-row">
            <span>Delivery</span>
            <span>{delivery === 0 ? "Free" : formatPrice(delivery)}</span>
          </div>
          <div className="summary-row total">
            <span>Total</span>
            <span>{formatPrice(total)}</span>
          </div>
        </aside>
      </div>
    </div>
  );
}

export default Checkout;
