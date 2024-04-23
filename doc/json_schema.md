# JSON Schemas

These are the schema that our API follows. There's no actual validation going
on, these are just guidelines to follow.

## /api/v1/advertisements

### GET:

response:

- 200 OK:

  ```
  {
    "ads": [
      {
        "id": int,
        "ad": string
      }
    ]
  }
  ```

### POST:

request

```
{
  "ad": string
}
```

response:

- 201 CREATED:

  ```
  {
    "id": int,
    "ad": string
  }
  ```

- 404 NOT FOUND:

  ```
  {
    "detail": string
  }
  ```

- 400 BAD REQUEST:

  ```
  {
    "detail": string
  }
  ```

### DELETE:

request:

```
{
  "id": int
}
```

response:

- 200 OK:

- 400 BAD REQUEST:

  ```
  {
    "detail": string
  }
  ```

## /api/v1/football

### GET:

response:

```
{
  "teamOne": {
    "name": string,
    "score": int
  },
  "teamTwo": {
    "name": string,
    "score": int
  },
  "down": int,
  "quarter": int,
  "timer": {
    "isRunning": bool,
    "time": int
  },
  "yards": int,
}
```

### PUT:

request:

```
{
  "anyOf": [
    {
      "teamOne": {
        "anyOf": [
          { "name": string },
          { "score": int }
        ]
      }
    },
    { "down": int },
    { "quarter": int },
    {
      "timer": {
        "anyOf": [
          { "isRunning": bool },
          { "time": int }
        ]
      }
    },
    { "yards": int },
  ]
}
```
