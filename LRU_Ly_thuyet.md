# LÝ THUYẾT THUẬT TOÁN LRU

## 1. LRU là gì?
LRU (Least Recently Used) là thuật toán thay thế bộ nhớ đệm. Khi bộ nhớ đệm đầy, thuật toán loại bỏ phần tử đã lâu nhất chưa được sử dụng.

LRU dựa trên giả định: dữ liệu vừa được sử dụng gần đây có khả năng tiếp tục được sử dụng trong tương lai gần. Dữ liệu lâu không được truy cập có khả năng ít quan trọng hơn.

LRU thường được dùng trong hệ điều hành, bộ nhớ đệm CPU, trình duyệt, máy chủ, cơ sở dữ liệu và các thư viện lưu kết quả tính toán.

## 2. Bài toán
Với bộ nhớ đệm có sức chứa tối đa `capacity`:
- Nếu khóa đã tồn tại, trả về giá trị và đánh dấu là vừa được sử dụng.
- Nếu khóa chưa tồn tại, thêm khóa mới.
- Nếu bộ nhớ đệm đầy, xóa khóa ít được sử dụng gần đây nhất.

Mục tiêu là thực hiện `get` và `put` trong thời gian trung bình `O(1)`.

## 3. Ý tưởng cốt lõi
LRU thường kết hợp hai cấu trúc dữ liệu:

### Hash Map
Lưu ánh xạ `key -> node trong danh sách liên kết đôi`, giúp tìm phần tử trong thời gian trung bình `O(1)`.

### Danh sách liên kết đôi
Lưu thứ tự sử dụng:

```text
MRU <-> ... <-> LRU
```

- Đầu danh sách: phần tử vừa được sử dụng gần đây nhất (MRU).
- Cuối danh sách: phần tử lâu nhất chưa được sử dụng (LRU).

Danh sách liên kết đôi cho phép xóa node bất kỳ, đưa node lên đầu và xóa node cuối trong `O(1)`.

## 4. Quy tắc hoạt động

### `get(key)`
1. Nếu `key` không tồn tại, trả về `-1` hoặc `null`.
2. Nếu tồn tại, lấy node từ Hash Map.
3. Di chuyển node lên đầu danh sách.
4. Trả về giá trị của node.

### `put(key, value)`
- Nếu `key` đã tồn tại: cập nhật giá trị và đưa node lên đầu.
- Nếu chưa tồn tại: tạo node, chèn vào đầu danh sách và lưu vào Hash Map.
- Nếu số phần tử vượt quá `capacity`: xóa node cuối danh sách và xóa khóa tương ứng khỏi Hash Map.

## 5. Ví dụ
Giả sử `capacity = 3` và thực hiện:

```text
put(A, 1)
put(B, 2)
put(C, 3)
get(A)
put(D, 4)
```

Sau ba lệnh đầu:

```text
A <-> B <-> C
MRU           LRU
```

Sau `get(A)`:

```text
A <-> C <-> B
MRU           LRU
```

Khi gọi `put(D, 4)`, B là phần tử ở cuối nên bị loại bỏ:

```text
D <-> A <-> C
MRU           LRU
```

Kết quả cuối cùng là A, C và D.

## 6. Giả mã

### Khởi tạo
```text
cache = HashMap()
head = node giả ở đầu danh sách
tail = node giả ở cuối danh sách
Nối head với tail
```

### Di chuyển node lên đầu
```text
moveToFront(node):
    Xóa node khỏi vị trí hiện tại
    Chèn node ngay sau head
```

### Lấy dữ liệu
```text
get(key):
    Nếu key không có trong cache:
        trả về -1

    node = cache[key]
    moveToFront(node)
    trả về node.value
```

### Thêm hoặc cập nhật dữ liệu
```text
put(key, value):
    Nếu key đã có trong cache:
        node = cache[key]
        node.value = value
        moveToFront(node)
        kết thúc

    node mới = Node(key, value)
    cache[key] = node
    Chèn node vào đầu danh sách

    Nếu số phần tử trong cache > capacity:
        node cần xóa = node ngay trước tail
        Xóa node cần xóa khỏi danh sách
        Xóa node cần xóa.key khỏi cache
```

## 7. Độ phức tạp
| Thao tác | Độ phức tạp trung bình | Bộ nhớ |
|---|---:|---:|
| `get` | `O(1)` | `O(capacity)` |
| `put` | `O(1)` | `O(capacity)` |
| Xóa phần tử cũ nhất | `O(1)` | `O(capacity)` |

## 8. Vì sao dùng danh sách liên kết đôi?
Danh sách liên kết đơn không thuận tiện khi xóa node bất kỳ vì cần biết node đứng trước nó. Danh sách liên kết đôi có `prev` và `next`, cho phép tháo node khỏi danh sách ngay lập tức. Hai node giả `head` và `tail` giúp giảm các trường hợp đặc biệt khi thêm hoặc xóa ở đầu/cuối.

## 9. Ưu điểm và hạn chế
### Ưu điểm
- `get` và `put` có thời gian trung bình `O(1)`.
- Phù hợp với bộ nhớ đệm có kích thước giới hạn.
- Dễ mở rộng để lưu thống kê hoặc thời điểm truy cập.

### Hạn chế
- Cần thêm bộ nhớ cho Hash Map và các con trỏ.
- Dễ phát sinh lỗi khi cập nhật liên kết nếu tự triển khai.
- Dữ liệu ít được dùng gần đây không phải lúc nào cũng ít quan trọng nhất.
- Môi trường đa luồng cần cơ chế đồng bộ.

## 10. So sánh
- **FIFO:** loại bỏ phần tử được thêm vào sớm nhất, không quan tâm tần suất truy cập.
- **LFU:** loại bỏ phần tử có số lần truy cập thấp nhất, thường phức tạp hơn LRU.
- **MRU:** loại bỏ phần tử vừa được sử dụng gần đây nhất, phù hợp với một số mẫu truy cập đặc biệt.

## 11. Kết luận
LRU loại bỏ phần tử lâu nhất chưa được sử dụng. Cách triển khai hiệu quả thường kết hợp Hash Map với danh sách liên kết đôi: Hash Map giúp tìm nhanh, còn danh sách liên kết đôi giúp cập nhật thứ tự sử dụng nhanh. Nhờ đó, `get` và `put` đạt độ phức tạp trung bình `O(1)`.
