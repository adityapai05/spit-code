import { useState } from "react";

function TodoForm({addTodo}) {
  const [todoTitle, setTodoTitle] = useState("");
  const handleSubmit = (e) => {
    e.preventDefault();
    addTodo(todoTitle);
    setTodoTitle("");
  }

  return (
    <form className="todo-form" onSubmit={handleSubmit}>
      <input
        className="todo-input"
        type="text"
        placeholder="What needs to be done?"
        onChange={(e) => setTodoTitle(e.target.value)}
        value={todoTitle}
      />
      <button className="btn btn-primary" type="submit">
        Add task
      </button>
    </form>
  );
}

export default TodoForm;
