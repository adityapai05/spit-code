function StudentDetails(props) {
  const s = props.student;

  return (
    <div className="details">
      <h2>Student Details</h2>
      <p>Name: {s.name}</p>
      <p>ID: {s.id}</p>
      <p>Class: {s.class}</p>
      <p>Status: {s.status}</p>
      <p>Attendance: {s.attendance}%</p>
      <p>
        Assignments: {s.assignmentsCompleted} out of {s.assignmentsTotal} completed
      </p>

      <h3>Subject Marks</h3>
      <ul>
        <li>Web Technology: {s.marks.web}</li>
        <li>Java: {s.marks.java}</li>
        <li>DBMS: {s.marks.dbms}</li>
        <li>Python: {s.marks.python}</li>
        <li>Maths: {s.marks.maths}</li>
      </ul>
      <p>Average Marks: {s.avgMarks.toFixed(1)}</p>

      {s.atRisk ? (
        <p style={{ color: "red" }}>
          This student is AT RISK (attendance below 75% or marks below 40)
        </p>
      ) : (
        <p style={{ color: "green" }}>This student is doing fine</p>
      )}

      <button onClick={props.onClose}>Close</button>
    </div>
  );
}

export default StudentDetails;
