import { PieChart, Pie, Tooltip, Cell, Legend } from "recharts";

export default function AttendancePieChart({ students }) {
  // students with attendance 75 or more are safe
  const safe = students.filter((s) => s.attendance >= 75).length;
  const low = students.filter((s) => s.attendance < 75).length;

  const data = [
    { name: "Attendance 75% or more", value: safe },
    { name: "Attendance below 75%", value: low },
  ];

  const COLORS = ["#4CAF50", "#F44336"];

  return (
    <div
      style={{ display: "flex", flexDirection: "column", alignItems: "center" }}
    >
      <h2 style={{ textAlign: "center" }}>Attendance Overview</h2>
      <PieChart width={450} height={300}>
        <Pie
          data={data}
          cx="50%"
          cy="50%"
          outerRadius={100}
          dataKey="value"
          label
        >
          {data.map((entry, index) => (
            <Cell key={index} fill={COLORS[index]} />
          ))}
        </Pie>
        <Tooltip />
        <Legend />
      </PieChart>
    </div>
  );
}
