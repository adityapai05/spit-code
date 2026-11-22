import { useState, useEffect } from "react";
import SummaryCards from "./components/SummaryCards";
import StudentTable from "./components/StudentTable";
import StudentDetails from "./components/StudentDetails";
import StudentBarChart from "./components/StudentBarChart";
import AttendancePieChart from "./components/AttendancePieChart";
import PerformanceLineChart from "./components/PerformanceLineChart";
import Leaderboard from "./components/Leaderboard";

function App() {
  const [students, setStudents] = useState([]);
  const [search, setSearch] = useState("");
  const [classFilter, setClassFilter] = useState("All");
  const [statusFilter, setStatusFilter] = useState("All");
  const [sortBy, setSortBy] = useState("none");
  const [selectedStudent, setSelectedStudent] = useState(null);

  // load json file
  useEffect(() => {
    fetch("/students.json")
      .then((res) => res.json())
      .then((data) => {
        // add average marks and at risk to every student
        const newData = data.map((s) => {
          const total = Object.values(s.marks).reduce((sum, m) => sum + m, 0);
          const avg = total / Object.values(s.marks).length;
          return {
            ...s,
            avgMarks: avg,
            atRisk: s.attendance < 75 || avg < 40,
          };
        });
        setStudents(newData);
      });
  }, []);

  // numbers for the cards
  const totalStudents = students.length;
  const totalAttendance = students.reduce((sum, s) => sum + s.attendance, 0);
  const avgAttendance = totalAttendance / totalStudents;
  const totalMarks = students.reduce((sum, s) => sum + s.avgMarks, 0);
  const avgMarks = totalMarks / totalStudents;
  const atRiskCount = students.filter((s) => s.atRisk).length;

  // search
  let filtered = students.filter(
    (s) =>
      s.name.toLowerCase().includes(search.toLowerCase()) ||
      s.id.toLowerCase().includes(search.toLowerCase())
  );

  // class filter
  if (classFilter !== "All") {
    filtered = filtered.filter((s) => s.class === classFilter);
  }

  // status filter
  if (statusFilter === "At Risk") {
    filtered = filtered.filter((s) => s.atRisk);
  } else if (statusFilter !== "All") {
    filtered = filtered.filter((s) => s.status === statusFilter);
  }

  // sorting
  if (sortBy === "name") {
    filtered = [...filtered].sort((a, b) => a.name.localeCompare(b.name));
  } else if (sortBy === "marks") {
    filtered = [...filtered].sort((a, b) => b.avgMarks - a.avgMarks);
  } else if (sortBy === "attendance") {
    filtered = [...filtered].sort((a, b) => a.attendance - b.attendance);
  }

  return (
    <div style={{ padding: "20px", fontFamily: "Arial" }}>
      <h1 style={{ textAlign: "center" }}>Smart Campus Analytics Dashboard</h1>

      <SummaryCards
        total={totalStudents}
        attendance={avgAttendance}
        marks={avgMarks}
        atRisk={atRiskCount}
      />

      <div
        style={{
          display: "grid",
          gridTemplateColumns: "1fr 1fr",
          gap: "30px",
          marginTop: "30px",
        }}
      >
        <StudentBarChart students={students} />
        <AttendancePieChart students={students} />
      </div>

      <div style={{ marginTop: "30px" }}>
        <PerformanceLineChart students={students} selectedStudent={selectedStudent} />
      </div>

      <h2>Student Records</h2>

      <div className="filters">
        <input
          type="text"
          placeholder="Search by name or ID"
          value={search}
          onChange={(e) => setSearch(e.target.value)}
        />

        <select value={classFilter} onChange={(e) => setClassFilter(e.target.value)}>
          <option value="All">All Classes</option>
          <option value="SYMCA-A">SYMCA-A</option>
          <option value="SYMCA-B">SYMCA-B</option>
        </select>

        <select value={statusFilter} onChange={(e) => setStatusFilter(e.target.value)}>
          <option value="All">All Status</option>
          <option value="Active">Active</option>
          <option value="Inactive">Inactive</option>
          <option value="At Risk">At Risk</option>
        </select>

        <select value={sortBy} onChange={(e) => setSortBy(e.target.value)}>
          <option value="none">Sort By</option>
          <option value="name">Name</option>
          <option value="marks">Marks (high to low)</option>
          <option value="attendance">Attendance (low to high)</option>
        </select>
      </div>

      <StudentTable students={filtered} onSelect={setSelectedStudent} />

      {selectedStudent && (
        <StudentDetails student={selectedStudent} onClose={() => setSelectedStudent(null)} />
      )}

      <Leaderboard students={students} />
    </div>
  );
}

export default App;
