function TodoFooter({todosLength}) {
  return (
    <footer className="todo-footer">
      <span>{todosLength} tasks remaining</span>
    </footer>
  );
}

export default TodoFooter;
