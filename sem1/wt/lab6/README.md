# Monsoon Co.

**Stay dry. Move freely.**

Monsoon Co. is a small React e-commerce store for monsoon essentials in India: rainwear, umbrellas, waterproof gear, footwear and accessories. It was built for the Web Technology Lab 6 practical.

## Features
- Home page with hero, featured products, categories and promo banner
- Product listing with category filter, min/max price filter, price sorting and clear filters
- Dynamic product details page (`/products/:productId`) with quantity selector
- Cart with add, increase, decrease, remove, item count, totals and free delivery above ₹999
- Cart saved in `localStorage`, so it survives a page refresh
- Checkout form with validation (required fields, email format, 10-digit mobile, 6-digit PIN)
- Cash on Delivery order, unique order ID, and order confirmation page
- Custom 404 page and a not-found state for invalid product IDs
- Responsive layout for mobile, tablet and desktop

## Technologies used
React 18, JavaScript, JSX, vanilla CSS, React Router DOM v6, `useState`, props, `localStorage`, Vite.
No Context API, Redux, TypeScript or CSS frameworks.

## Folder structure
```text
monsoon-co/
├── public/images/        product images (local SVG files)
├── src/
│   ├── components/       Header, Footer, ProductCard, CartItem, ScrollToTop
│   ├── pages/            Home, Products, ProductDetails, Cart, Checkout, OrderConfirmation, NotFound
│   ├── data/             products.js (product list), pricing.js (totals and delivery helper)
│   ├── App.jsx           routes + cart state
│   ├── main.jsx          BrowserRouter wrapper
│   └── index.css         all styles
├── index.html
├── package.json
└── README.md
```

## Installation and running
```bash
npm install
npm run dev
```
