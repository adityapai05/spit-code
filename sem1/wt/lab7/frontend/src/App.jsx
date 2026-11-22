import { useState, useEffect } from "react";
import "./App.css";

const API = "/books";

function App() {
  const [books, setBooks] = useState([]);
  const [title, setTitle] = useState("");
  const [author, setAuthor] = useState("");
  const [editId, setEditId] = useState(null); // null means we are adding, not editing

  // READ - get all books
  async function getBooks() {
    const res = await fetch(API);
    const data = await res.json();
    setBooks(data);
  }

  // run once when page loads
  useEffect(() => {
    getBooks();
  }, []);

  // CREATE and UPDATE both happen on form submit
  async function handleSubmit(e) {
    e.preventDefault();

    if (title === "" || author === "") {
      alert("Please fill both fields");
      return;
    }

    if (editId === null) {
      // CREATE
      await fetch(API, {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ title: title, author: author }),
      });
    } else {
      // UPDATE
      await fetch(API + "/" + editId, {
        method: "PUT",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ title: title, author: author }),
      });
      setEditId(null);
    }

    setTitle("");
    setAuthor("");
    getBooks();
  }

  // put the book data into the form so we can edit it
  function handleEdit(book) {
    setEditId(book.id);
    setTitle(book.title);
    setAuthor(book.author);
  }

  function handleCancel() {
    setEditId(null);
    setTitle("");
    setAuthor("");
  }

  // DELETE
  async function handleDelete(id) {
    await fetch(API + "/" + id, { method: "DELETE" });
    getBooks();
  }

  return (
    <div className="container">
      <h1>Library Management System</h1>

      <form onSubmit={handleSubmit}>
        <input
          type="text"
          placeholder="Title"
          value={title}
          onChange={(e) => setTitle(e.target.value)}
        />
        <input
          type="text"
          placeholder="Author"
          value={author}
          onChange={(e) => setAuthor(e.target.value)}
        />
        <button type="submit">
          {editId === null ? "Add Book" : "Update Book"}
        </button>
        {editId !== null && (
          <button type="button" onClick={handleCancel}>
            Cancel
          </button>
        )}
      </form>

      <table>
        <thead>
          <tr>
            <th>ID</th>
            <th>Title</th>
            <th>Author</th>
            <th>Actions</th>
          </tr>
        </thead>
        <tbody>
          {books.map((book) => (
            <tr key={book.id}>
              <td>{book.id}</td>
              <td>{book.title}</td>
              <td>{book.author}</td>
              <td>
                <button className="edit" onClick={() => handleEdit(book)}>Edit</button>
                <button className="delete" onClick={() => handleDelete(book.id)}>Delete</button>
              </td>
            </tr>
          ))}
        </tbody>
      </table>

      {books.length === 0 && <p>No books yet.</p>}
    </div>
  );
}

export default App;
