import {
  LineChart,
  Line,
  XAxis,
  YAxis,
  CartesianGrid,
  Tooltip,
  Legend,
} from "recharts";

// average score of the class in every test
// if a student is clicked in the table his line is also shown
export default function PerformanceLineChart({ students, selectedStudent }) {
  const data = [];

  if (students.length > 0) {
    for (let i = 0; i < students[0].tests.length; i++) {
      const total = students.reduce((sum, s) => sum + s.tests[i], 0);
      const row = {
        test: "Test " + (i + 1),
        classAverage: Math.round(total / students.length),
      };
      if (selectedStudent) {
        row.student = selectedStudent.tests[i];
      }
      data.push(row);
    }
  }

  return (
    <div
      style={{ display: "flex", flexDirection: "column", alignItems: "center" }}
    >
      <h2 style={{ textAlign: "center" }}>Test Performance Trend</h2>
      <LineChart width={900} height={300} data={data}>
        <CartesianGrid strokeDasharray="3 3" />
        <XAxis dataKey="test" />
        <YAxis domain={[0, 100]} />
        <Tooltip />
        <Legend />
        <Line
          type="monotone"
          dataKey="classAverage"
          stroke="#82ca9d"
          isAnimationActive={false}
        />
        {selectedStudent && (
          <Line
            type="monotone"
            dataKey="student"
            stroke="#8884d8"
            name={selectedStudent.name}
            isAnimationActive={false}
          />
        )}
      </LineChart>
    </div>
  );
}
