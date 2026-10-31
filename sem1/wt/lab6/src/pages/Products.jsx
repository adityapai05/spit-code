import { useState } from "react";
import ProductCard from "../components/ProductCard.jsx";
import products, { categories } from "../data/products.js";

function Products({ addToCart }) {
  const [selectedCategory, setSelectedCategory] = useState("All");
  const [minPrice, setMinPrice] = useState("");
  const [maxPrice, setMaxPrice] = useState("");
  const [sortOrder, setSortOrder] = useState("none");

  let visibleProducts = products.filter((product) => {
    const categoryMatch =
      selectedCategory === "All" || product.category === selectedCategory;
    const minMatch = minPrice === "" || product.price >= Number(minPrice);
    const maxMatch = maxPrice === "" || product.price <= Number(maxPrice);
    return categoryMatch && minMatch && maxMatch;
  });

  if (sortOrder === "low") {
    visibleProducts = [...visibleProducts].sort((a, b) => a.price - b.price);
  } else if (sortOrder === "high") {
    visibleProducts = [...visibleProducts].sort((a, b) => b.price - a.price);
  }

  function clearFilters() {
    setSelectedCategory("All");
    setMinPrice("");
    setMaxPrice("");
    setSortOrder("none");
  }

  return (
    <div className="container section">
      <h1 className="page-title">Shop</h1>

      <div className="filters">
        <label>
          Category
          <select
            value={selectedCategory}
            onChange={(e) => setSelectedCategory(e.target.value)}
          >
            <option value="All">All categories</option>
            {categories.map((name) => (
              <option key={name} value={name}>
                {name}
              </option>
            ))}
          </select>
        </label>
        <label>
          Min price (₹)
          <input
            type="number"
            min="0"
            value={minPrice}
            onChange={(e) => setMinPrice(e.target.value)}
            placeholder="0"
          />
        </label>
        <label>
          Max price (₹)
          <input
            type="number"
            min="0"
            value={maxPrice}
            onChange={(e) => setMaxPrice(e.target.value)}
            placeholder="5000"
          />
        </label>
        <label>
          Sort by
          <select
            value={sortOrder}
            onChange={(e) => setSortOrder(e.target.value)}
          >
            <option value="none">Featured</option>
            <option value="low">Price: Low to High</option>
            <option value="high">Price: High to Low</option>
          </select>
        </label>
        <button className="btn btn-outline" onClick={clearFilters}>
          Clear filters
        </button>
      </div>

      <p className="muted result-count">
        Showing {visibleProducts.length} of {products.length} products
      </p>

      {visibleProducts.length === 0 ? (
        <div className="empty-box">
          <h3>No products match these filters</h3>
          <p className="muted">
            Try a different price range or clear the filters.
          </p>
          <button className="btn btn-primary" onClick={clearFilters}>
            Clear filters
          </button>
        </div>
      ) : (
        <div className="product-grid">
          {visibleProducts.map((product) => (
            <ProductCard
              key={product.id}
              product={product}
              addToCart={addToCart}
            />
          ))}
        </div>
      )}
    </div>
  );
}

export default Products;
