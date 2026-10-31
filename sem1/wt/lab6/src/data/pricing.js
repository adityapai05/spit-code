export const FREE_DELIVERY_ABOVE = 999;
export const DELIVERY_CHARGE = 79;

export function formatPrice(amount) {
  return "₹" + amount.toLocaleString("en-IN");
}

export function getTotals(cart) {
  const totalItems = cart.reduce((sum, item) => sum + item.quantity, 0);
  const subtotal = cart.reduce(
    (sum, item) => sum + item.price * item.quantity,
    0,
  );
  const delivery =
    subtotal === 0 || subtotal > FREE_DELIVERY_ABOVE ? 0 : DELIVERY_CHARGE;
  return { totalItems, subtotal, delivery, total: subtotal + delivery };
}
