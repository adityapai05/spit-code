function TodoFilters({ filter, setFilter }) {
  return (
    <div className="todo-filters">
      <button
        className={`filter-btn ${filter === "all" ? "active" : ""}`}
        type="button"
        onClick={() => setFilter("all")}
      >
        All
      </button>

      <button
        className={`filter-btn ${filter === "active" ? "active" : ""}`}
        type="button"
        onClick={() => setFilter("active")}
      >
        Active
      </button>

      <button
        className={`filter-btn ${filter === "completed" ? "active" : ""}`}
        type="button"
        onClick={() => setFilter("completed")}
      >
        Completed
      </button>
    </div>
  );
}

export default TodoFilters;
