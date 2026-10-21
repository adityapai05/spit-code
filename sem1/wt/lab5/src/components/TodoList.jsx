import TodoItem from "./TodoItem";

function TodoList({ todos, updateTodos, deleteTodo }) {
  if (todos.length === 0) {
    return <p className="empty-message">No todos to display</p>;
  }

  return (
    <ul className="todo-list">
      {todos.map((todo) => (
        <TodoItem
          key={todo.id}
          id={todo.id}
          title={todo.title}
          completed={todo.completed}
          updateTodos={updateTodos}
          deleteTodo={deleteTodo}
        />
      ))}
    </ul>
  );
}

export default TodoList;
