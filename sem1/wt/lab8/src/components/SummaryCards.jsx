function SummaryCards(props) {
  return (
    <div className="cards">
      <div className="card">
        <h3>Total Students</h3>
        <p>{props.total}</p>
      </div>
      <div className="card">
        <h3>Average Attendance</h3>
        <p>{props.attendance.toFixed(1)}%</p>
      </div>
      <div className="card">
        <h3>Average Marks</h3>
        <p>{props.marks.toFixed(1)}</p>
      </div>
      <div className="card">
        <h3>At-Risk Students</h3>
        <p style={{ color: "red" }}>{props.atRisk}</p>
      </div>
    </div>
  );
}

export default SummaryCards;
