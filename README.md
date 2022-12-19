# PBL2.version2_4
- Ngày 12/11/2022:
  + Thêm destructor để giải phóng vùng nhớ cho class HeThong
  + Chỉnh sửa chức năng chỉnh sửa từ vựng: khi thay đổi nghĩa 
  của từ vựng thì xoá đi tất cả nghĩa của từ vựng này đã lưu 
  trước đó tại hashtableMeaning và bây giờ thêm nghĩa mới vào
  bảng băm hashtableMeaning
  +Chỉnh sửa chức năng xoá: xoá từ thì xoá luôn các nghĩa đi kèm với
- Ngày 23/11/2022:
  + Sửa lỗi không tra cứu từ vựng được khi từ tiếng việt nhập vào là unicode in hoa 
  (vd gửi Đi thì ko tìm thấy) bằng cách sửa lại hàm convert (setLocale(...))
  + Khi đăng nhập mà tài khoản hoặc mật khẩu không nhập gì mà bấm enter là không
  cho phép
 - 19/12/2022: update giao diện phần hiển thị từ điển hệ thống, sửa chức năng đổi mk cho admin và dùng mk mới đó 
cho lần đăng nhập tiếp theo,tại chức năng thêm từ vựng của người dùng cho phép người dùng thêm thủ công
![PBL2](https://user-images.githubusercontent.com/108993284/203814411-c69bb3bc-085a-453a-b06e-4bf71f221d16.png)
