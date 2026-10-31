import { useState, useEffect } from "react";
import { Routes, Route } from "react-router-dom";
import Header from "./components/Header.jsx";
import Footer from "./components/Footer.jsx";
import ScrollToTop from "./components/ScrollToTop.jsx";
import Home from "./pages/Home.jsx";
import Products from "./pages/Products.jsx";
import ProductDetails from "./pages/ProductDetails.jsx";
import Cart from "./pages/Cart.jsx";
import Checkout from "./pages/Checkout.jsx";
import OrderConfirmation from "./pages/OrderConfirmation.jsx";
import NotFound from "./pages/NotFound.jsx";

function loadSavedCart() {
  try {
    const saved = localStorage.getItem("monsoonCart");
    return saved ? JSON.parse(saved) : [];
  } catch (error) {
    return [];
  }
}

function App() {
  const [cart, setCart] = useState(loadSavedCart);
  const [order, setOrder] = useState(null);

  useEffect(() => {
    localStorage.setItem("monsoonCart", JSON.stringify(cart));
  }, [cart]);

  function addToCart(product, quantity = 1) {
    const existing = cart.find((item) => item.id === product.id);
    if (existing) {
      setCart(
        cart.map((item) =>
          item.id === product.id
            ? { ...item, quantity: item.quantity + quantity }
            : item,
        ),
      );
    } else {
      setCart([
        ...cart,
        {
          id: product.id,
          name: product.name,
          price: product.price,
          image: product.image,
          quantity: quantity,
        },
      ]);
    }
  }

  return (
    <>
      <ScrollToTop />
      <Header cart={cart} />
      <main>
        <Routes>
          <Route path="/" element={<Home addToCart={addToCart} />} />
          <Route
            path="/products"
            element={<Products addToCart={addToCart} />}
          />
          <Route
            path="/products/:productId"
            element={<ProductDetails addToCart={addToCart} />}
          />
          <Route
            path="/cart"
            element={<Cart cart={cart} setCart={setCart} />}
          />
          <Route
            path="/checkout"
            element={
              <Checkout cart={cart} setCart={setCart} setOrder={setOrder} />
            }
          />
          <Route
            path="/order-confirmation"
            element={<OrderConfirmation order={order} />}
          />
          <Route path="*" element={<NotFound />} />
        </Routes>
      </main>
      <Footer />
    </>
  );
}

export default App;
