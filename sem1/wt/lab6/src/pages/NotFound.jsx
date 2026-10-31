import { Link } from "react-router-dom";

function NotFound() {
  return (
    <div className="container section center-box">
      <div className="empty-art">404</div>
      <h1>This page got rained out</h1>
      <p className="muted">
        The page you are looking for does not exist or has moved.
      </p>
      <Link to="/" className="btn btn-primary">
        Back to home
      </Link>
    </div>
  );
}

export default NotFound;
