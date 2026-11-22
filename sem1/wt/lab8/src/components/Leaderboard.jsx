// additional feature - top 5 students
function Leaderboard({ students }) {
  const sorted = [...students].sort((a, b) => b.avgMarks - a.avgMarks);
  const top5 = sorted.slice(0, 5);

  return (
    <div>
      <h2>Performance Leaderboard (Top 5)</h2>
      <table>
        <thead>
          <tr>
            <th>Rank</th>
            <th>Name</th>
            <th>Class</th>
            <th>Avg Marks</th>
          </tr>
        </thead>
        <tbody>
          {top5.map((s, index) => (
            <tr key={s.id}>
              <td>{index + 1}</td>
              <td>{s.name}</td>
              <td>{s.class}</td>
              <td>{s.avgMarks.toFixed(1)}</td>
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );
}

export default Leaderboard;
