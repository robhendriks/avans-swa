## Specification

### Sprite

**Properties**

| Name      | Type   | Description      | Required |
| :-------- | :----- | :--------------- | :------: |
| id        | String | Unique sprite ID | yes      |
| image     | Object | Image object     | yes      |
| image.url | String | Image path       | yes      |

```json
{
  "id": "enemy-a-sprite",
  "image": {
    "url": "/relative/image.jpg"
  }
}
```

### Object

**Properties**

| Name          | Type   | Description               | Required |
| :------------ | :----- | :------------------------ | :------: |
| id            | String | Unique object ID          | yes      |
| states        | Array  | State array               | no       |
| states.{name} | Array  | Array with row and column | no       |

```json
{
  "id": "enemy-a",
  "sprite": "enemy-a-sprite",
  "states": {
    "idle": [0, 0],
    "walk": [
      [0, 1],
      [1, 1],
      [2, 1]
    ],
    "attack": [
      [0, 2],
      [1, 2]
    ],
    "dead": [0, 3]
  }
}
```
