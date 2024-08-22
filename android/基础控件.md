## 新建activity

1. 创建activity类

```java
public class MainActivity2 extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);

    }
}
```

2. 创建对应layout

```xml
<?xml version="1.0" encoding="utf-8"?>
<LinearLayout xmlns:android="http://schemas.android.com/apk/res/android"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:orientation="vertical"
    android:layout_gravity="center"
    >

    <TextView
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:text="@string/text2"
        />
</LinearLayout>
```



3. AndroidManifest注册activity

```xml
<activity android:name=".MainActivity2" />
```

## 控件属性

### 颜色

```xml
android:text="系统自带绿色"
android:textSize="18sp"
android:textColor="#eeff40"

tvCodeBackground.setBackgroundColor(0xffee11cc);
tvCodeBackground.setBackgroundResource();
```

### 宽高

```xml
 <TextView
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:id="@+id/tv1"
        android:text="代码中设置"
        android:textSize="20sp"
        android:textColor="#8829e140"
        tools:ignore="HardcodedText" />
```

### 代码中设置宽高

```xml
<TextView
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:id="@+id/tv1"
        android:text="代码中设置"
        android:textSize="20sp"
        android:textColor="#8829e140"
        tools:ignore="HardcodedText" />
```

```java
 protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_text_color);
        TextView tv1 = findViewById(R.id.tv1);
        ViewGroup.LayoutParams layoutParams = tv1.getLayoutParams();
        layoutParams.height=dip2px(this,300); //必须要 wrap_content
        tv1.setLayoutParams(layoutParams);

    }
//dp转为像素
    public static int dip2px(Context ctx,float dp){
        float dpi =  ctx.getResources().getDisplayMetrics().density;
        return (int)(dp * dpi+0.5f);
    }
```

### 设置边距

```xml
<?xml version="1.0" encoding="utf-8"?>
<LinearLayout xmlns:android="http://schemas.android.com/apk/res/android"
    android:layout_width="match_parent"
    android:layout_height="300dp"
    android:orientation="vertical"
    android:background="#00aaff"
    >
    <LinearLayout
        android:layout_width="match_parent"
        android:layout_height="match_parent"
        android:background="#ffff99"
        android:layout_margin="20dp"
        android:padding="60dp"
        >
<!--layout_margin设置与周围布局的间距-->
<!-- padding设置当前布局与内容器的边距-->
        <View
            android:layout_width="match_parent"
            android:layout_height="match_parent"
            android:background="#ff0000"
            />
    </LinearLayout>
</LinearLayout>
```

<img src="/lab1img/margin.png" alt="margin" style="zoom: 25%;" />

layout_margin适用于View子类

### 对齐方式

 ```xml
 <?xml version="1.0" encoding="utf-8"?>
 <LinearLayout xmlns:android="http://schemas.android.com/apk/res/android"
     android:layout_width="match_parent"
     android:layout_height="300dp"
     android:background="#ffff99"
     android:orientation="horizontal"
     >
     <LinearLayout
         android:layout_width="match_parent"
         android:layout_height="0dp"
         android:layout_margin="10dp"
         android:background="#ff0000"
         android:layout_weight="1"
         android:padding="10dp"
         android:layout_gravity="bottom"
         android:gravity="left"
         >
 <!--        layout_gravity设置此容器在外面的对齐方式
             gravity设置内容器的对齐方式
 			weight或height设为0，采用权重layout_weight	
 -->
         <View
             android:layout_width="100dp"
             android:layout_height="100dp"
             android:background="#e93282"
             />
     </LinearLayout>
     <LinearLayout
         android:layout_width="match_parent"
         android:layout_height="200dp"
         android:layout_margin="10dp"
         android:background="#ff00ee"
         android:layout_weight="1"
         android:padding="10dp"
         android:layout_gravity="top"
         android:gravity="right"
         >
         <View
             android:layout_width="100dp"
             android:layout_height="100dp"
             android:background="#598822"
             />
     </LinearLayout>
 </LinearLayout>
 ```

<img src="lab1img\gravity.png" alt="gravity" style="zoom:50%;" />

### 相对布局

![relative](C:\笔记\android\lab1img\relative.png)

### 网格布局

```xml
<?xml version="1.0" encoding="utf-8"?>
<GridLayout xmlns:android="http://schemas.android.com/apk/res/android"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:rowCount="2"
    android:columnCount="2"
    >
    <TextView
        android:text="00"
        android:textSize="50dp"
        android:background="#778811"
        android:layout_height="100dp"
        android:layout_width="0dp"
        android:layout_columnWeight="1"
        />
    <TextView
        android:text="01"
        android:textSize="50dp"
        android:background="#0088e1"
        android:layout_height="100dp"
        android:layout_width="0dp"
        android:layout_columnWeight="1"
        />
    <TextView
        android:text="10"
        android:textSize="50dp"
        android:background="#22e143"
        android:layout_height="100dp"
        android:layout_width="0dp"
        android:layout_columnWeight="1"
        />
    <TextView
        android:text="11"
        android:textSize="50dp"
        android:background="#22e1ff"
        android:layout_height="100dp"
        android:layout_width="0dp"
        android:layout_columnWeight="1"
        />
</GridLayout>
```

<img src="lab1img\grid.png" alt="grid" style="zoom:38%;" />
