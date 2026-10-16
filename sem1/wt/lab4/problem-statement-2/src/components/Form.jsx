import { useState } from "react";

function Form() {
  const [name, setName] = useState("");
  const [email, setEmail] = useState("");
  const [message, setMessage] = useState("");
  const [data, setData] = useState(null);

  function submitForm(e) {
    e.preventDefault();

    setData({
      name: name,
      email: email,
      message: message,
    });

    setName("");
    setEmail("");
    setMessage("");
  }

  return (
    <div className="form">
      <h2>Get in Touch</h2>
      <p>Fill in the details below to contact us.</p>

      <form onSubmit={submitForm}>
        <label>Name:</label>
        <input
          type="text"
          value={name}
          onChange={(e) => setName(e.target.value)}
          required
        />

        <label>Email:</label>
        <input
          type="email"
          value={email}
          onChange={(e) => setEmail(e.target.value)}
          required
        />

        <label>Message:</label>
        <textarea
          value={message}
          onChange={(e) => setMessage(e.target.value)}
          required
        ></textarea>

        <button type="submit">Send Message</button>
      </form>

      {data && (
        <div className="result">
          <h3>Form Details</h3>
          <p>Name: {data.name}</p>
          <p>Email: {data.email}</p>
          <p>Message: {data.message}</p>
        </div>
      )}
    </div>
  );
}

export default Form;
