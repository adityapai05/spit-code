function StudentTable(props) {
  if (props.students.length === 0) {
    return <p>No students found</p>;
  }

  return (
    <table>
      <thead>
        <tr>
          <th>ID</th>
          <th>Name</th>
          <th>Class</th>
          <th>Attendance</th>
          <th>Avg Marks</th>
          <th>Assignments</th>
          <th>Status</th>
        </tr>
      </thead>
      <tbody>
        {props.students.map((s) => (
          <tr
            key={s.id}
            onClick={() => props.onSelect(s)}
            style={{ backgroundColor: s.atRisk ? "#ffdddd" : "white", cursor: "pointer" }}
          >
            <td>{s.id}</td>
            <td>{s.name}</td>
            <td>{s.class}</td>
            <td>{s.attendance}%</td>
            <td>{s.avgMarks.toFixed(1)}</td>
            <td>
              {s.assignmentsCompleted}/{s.assignmentsTotal}
            </td>
            <td>{s.status}</td>
          </tr>
        ))}
      </tbody>
    </table>
  );
}

export default StudentTable;
