import {
  BarChart,
  Bar,
  XAxis,
  YAxis,
  CartesianGrid,
  Tooltip,
  Legend,
} from "recharts";

// average marks of all students in each subject
export default function StudentBarChart({ students }) {
  const subjects = ["web", "java", "dbms", "python", "maths"];
  const names = ["Web Tech", "Java", "DBMS", "Python", "Maths"];

  const data = subjects.map((sub, i) => {
    const total = students.reduce((sum, s) => sum + s.marks[sub], 0);
    return { subject: names[i], marks: Math.round(total / students.length) };
  });

  return (
    <div
      style={{ display: "flex", flexDirection: "column", alignItems: "center" }}
    >
      <h2 style={{ textAlign: "center" }}>Average Marks in Each Subject</h2>
      <BarChart width={500} height={300} data={data}>
        <CartesianGrid strokeDasharray="3 3" />
        <XAxis dataKey="subject" />
        <YAxis />
        <Tooltip />
        <Legend />
        <Bar dataKey="marks" fill="#8884d8" />
      </BarChart>
    </div>
  );
}
