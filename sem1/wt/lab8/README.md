# Lab 8: Smart Campus Analytics Dashboard

React dashboard that shows attendance, marks and assignment details of SYMCA students.
Data comes from `public/students.json`. No backend is used.

## How to run

```
npm install
npm run dev
```

Then open the link shown in the terminal (usually http://localhost:5173).

## Features

- Summary cards: total students, average attendance, average marks, at-risk students
- Bar chart: average marks in each subject
- Pie chart: students with attendance 75% or more vs below 75%
- Line chart: average class score in each test (a student's line is added when a row is clicked)
- Student table with search (name or ID), class filter, status filter (including At Risk) and sorting
- At-risk students: attendance below 75% or average marks below 40 (shown in red rows)
- Click a row to see the student details
- Additional feature: performance leaderboard (top 5 by average marks)

All values are calculated from the JSON file, nothing is typed by hand.

## React concepts used

- Functional components and props
- useState and useEffect (fetch the JSON)
- Conditional rendering and event handling
- map(), filter(), reduce() and sort()
- Recharts

## Folder structure

```
public/students.json
src/
  components/
    SummaryCards.jsx, StudentTable.jsx, StudentDetails.jsx,
    StudentBarChart.jsx, AttendancePieChart.jsx,
    PerformanceLineChart.jsx, Leaderboard.jsx
  App.jsx
  App.css
  main.jsx
```
