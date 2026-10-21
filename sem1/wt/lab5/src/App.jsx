import TodoForm from "./components/TodoForm";
import TodoList from "./components/TodoList";
import TodoFilters from "./components/TodoFilters";
import TodoFooter from "./components/TodoFooter";
import "./App.css";
import { useState } from "react";

function App() {
  const [todos, setTodos] = useState([]);
  const [filter, setFilter] = useState('all');
  const addTodo = (todoTitle) => {
    const todo = {
      id: crypto.randomUUID(),
      title: todoTitle,
      completed: false,
    };
    setTodos((currentTodos) => {
      return [...currentTodos, todo];
    });
  };

  const updateTodos = (id) => {
    setTodos((currentTodos) => {
      return currentTodos.map((todo) => {
        if (todo.id === id) {
          return {
            ...todo,
            completed: !todo.completed,
          };
        }

        return todo;
      });
    });
  };

  const deleteTodo = (id) => {
    setTodos((currentTodos) => {
      return currentTodos.filter((todo) => todo.id !== id);
    });
  };

  const filteredTodos = (filter) => {
    return todos.filter((todo) => {
      if (filter == "active") {
        return todo.completed == false;
      } else if (filter == "completed") {
        return todo.completed == true;
      }
      else if(filter == "all") {
        return true;
      }
    });
  };

  return (
    <main className="app">
      <header className="app-header">
        <h1>My Todos</h1>
        <p>Keep track of what you need to get done.</p>
      </header>

      <section className="todo-card">
        <TodoForm addTodo={addTodo} />
        <TodoFilters filter={filter} setFilter={setFilter} />
        <TodoList
          todos={filteredTodos(filter)}
          updateTodos={updateTodos}
          deleteTodo={deleteTodo}
        />
        <TodoFooter todosLength={filteredTodos("active").length} />
      </section>
    </main>
  );
}

export default App;
