1.添加Fragment类和布局

<img src="fragmentImg\a添加fragment类和布局.png" alt="a添加fragment类和布局" style="zoom:33%;" />

2.在res目录添加Navigation图

<img src="fragmentImg\b添加导航图.png" alt="b添加导航图" style="zoom:33%;" />

3.所属activity里添加FragmentContainerView

<img src="fragmentImg\c所属activity里添加FragmentContainerView.png" alt="c所属activity里添加FragmentContainerView" style="zoom:33%;" />

```xml
  <androidx.fragment.app.FragmentContainerView
        android:id="@+id/fragment"
        android:name="androidx.navigation.fragment.NavHostFragment"
        android:layout_width="match_parent"
        android:layout_height="match_parent"
        app:defaultNavHost="true"
        app:layout_constraintStart_toStartOf="parent"
        app:layout_constraintTop_toTopOf="parent"
        app:navGraph="@navigation/my_nav1" />
```

4.在Fragment类添加点击导航事件

<img src="fragmentImg\d在Fragment类添加点击导航事件.png" alt="d在Fragment类添加点击导航事件" style="zoom:33%;" />

5.所属activity添加显示导航条

<img src="fragmentImg\e所属activity添加显示导航条.png" alt="e所属activity添加显示导航条" style="zoom:25%;" />

或改成Fragment，就可以在onCreate方法获取NavController