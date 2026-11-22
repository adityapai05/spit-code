import express from "express";

const app = express();
const PORT = 3000;

// to read json from the request body
app.use(express.json());

// in memory array, data is lost when server restarts
let books = [
  { id: 1, title: "Harry Potter", author: "J.K. Rowling" },
  { id: 2, title: "The Alchemist", author: "Paulo Coelho" },
];

// id counter so every new book gets a new id
let nextId = 3;

// GET all books
app.get("/books", (req, res) => {
  res.json(books);
});

// GET one book
app.get("/books/:id", (req, res) => {
  const id = Number(req.params.id);
  const book = books.find((b) => b.id === id);

  if (!book) {
    return res.status(404).json({ message: "Book not found" });
  }

  res.json(book);
});

// POST add a book
app.post("/books", (req, res) => {
  const { title, author } = req.body;

  if (!title || !author) {
    return res.status(400).json({ message: "title and author are required" });
  }

  const newBook = { id: nextId, title: title, author: author };
  nextId++;

  books.push(newBook);
  res.status(201).json(newBook);
});

// PUT update a book
app.put("/books/:id", (req, res) => {
  const id = Number(req.params.id);
  const { title, author } = req.body;

  const book = books.find((b) => b.id === id);

  if (!book) {
    return res.status(404).json({ message: "Book not found" });
  }

  book.title = title;
  book.author = author;

  res.json(book);
});

// DELETE a book
app.delete("/books/:id", (req, res) => {
  const id = Number(req.params.id);

  const book = books.find((b) => b.id === id);
  if (!book) {
    return res.status(404).json({ message: "Book not found" });
  }

  // keep everything except the book we want to delete
  books = books.filter((b) => b.id !== id);

  res.json({ message: "Book deleted" });
});

app.listen(PORT, () => {
  console.log("Server running on http://localhost:" + PORT);
});
