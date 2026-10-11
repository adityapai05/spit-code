-- This table stores the games in each user's library.
-- status is one of: want-to-play, playing, completed
create table if not exists library (
  id bigint generated always as identity primary key,
  user_id uuid not null default auth.uid() references auth.users (id) on delete cascade,
  game_id integer not null,
  game_name text not null,
  game_image text,
  status text not null default 'want-to-play'
    check (status in ('want-to-play', 'playing', 'completed')),
  created_at timestamptz not null default now(),
  unique (user_id, game_id)
);

-- Row level security: every user can only see and change their own rows
alter table library enable row level security;

create policy "see own library" on library
  for select to authenticated using (auth.uid() = user_id);

create policy "add to own library" on library
  for insert to authenticated with check (auth.uid() = user_id);

create policy "change own library" on library
  for update to authenticated using (auth.uid() = user_id) with check (auth.uid() = user_id);

create policy "remove from own library" on library
  for delete to authenticated using (auth.uid() = user_id);

grant select, insert, update, delete on library to authenticated;
