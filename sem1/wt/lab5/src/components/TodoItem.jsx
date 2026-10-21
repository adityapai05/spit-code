function TodoItem({ id, title, completed, updateTodos, deleteTodo }) {
  return (
    <li className={`todo-item ${completed ? "completed" : ""}`}>
      <input
        className="todo-checkbox"
        type="checkbox"
        checked={completed}
        aria-label="Mark task as complete"
        onChange={() => updateTodos(id)}
      />

      <span className="todo-text">{title}</span>

      <div className="todo-actions">
        <button className="btn btn-danger" type="button" onClick={() => deleteTodo(id)}>
          Delete
        </button>
      </div>
    </li>
  );
}

export default TodoItem;
