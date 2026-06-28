addEvent = async (event, env) => {
  const sql = `INSERT INTO attendance_events
    (student_id, event_type, timestamp, device_id, sequence_number)
    VALUES (?, ?, ?, ?, ?)`;

  await env.DB.prepare(sql)
    .bind(event.studentId, event.type, event.timestamp, event.deviceId, event.sequence)
    .run();

  return new Response(JSON.stringify({ success: true }), { status: 200 });
};

getStatus = async (env) => {
  const rows = await env.DB.prepare(
    `SELECT student_id, event_type, timestamp, device_id FROM attendance_events
     ORDER BY timestamp DESC LIMIT 100`
  ).all();

  return new Response(JSON.stringify({ events: rows.results }), {
    status: 200,
    headers: { 'Content-Type': 'application/json' },
  });
};

export default {
  async fetch(request, env) {
    const url = new URL(request.url);

    if (request.method === 'POST' && url.pathname === '/events') {
      const event = await request.json();
      return addEvent(event, env);
    }

    if (request.method === 'GET' && url.pathname === '/status') {
      return getStatus(env);
    }

    return new Response('Not Found', { status: 404 });
  },
};
