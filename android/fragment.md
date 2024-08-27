

## Navigation

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

## Navigation 传递数据

```java
 public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        Button button = getView().findViewById(R.id.button);
        nameEdit = getView().findViewById(R.id.editTextText);
        button.setOnClickListener(v->{
            String name = nameEdit.getText().toString();
            Bundle bundle = new Bundle();
            bundle.putString("name",name);
            nameEdit.setText("");
            NavController navController = Navigation.findNavController(v);
            navController.navigate(R.id.action_homeFragment_to_dataFragment,bundle);
        });
    }
```

bundle添加数据

```java
 public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        Button button = getView().findViewById(R.id.button2);
        button.setOnClickListener(v->{
            NavController navController = Navigation.findNavController(v);
            navController.navigate(R.id.action_dataFragment_to_homeFragment);
        });
        nameText = getView().findViewById(R.id.dataText);
        String name = getArguments().getString("name");
        if (TextUtils.isEmpty(name)){
            Toast.makeText(getActivity(),"no name", Toast.LENGTH_SHORT).show();
        }else{
          nameText.setText("Hello :"+name);
        }
    }
```

## 自定义动画

```xml
<?xml version="1.0" encoding="utf-8"?>
<set xmlns:android="http://schemas.android.com/apk/res/android">
    <translate android:fromXDelta="-100%" android:toXDelta="0%" android:duration="300" >
    </translate>
</set>
```

## 数据双向绑定

xml声明变量，number和ViewModel的getter有关

```xml
<data>
        <variable
            name="n"
            type="com.example.viewmodelnav.MyViewModel" />
    </data>

    <androidx.constraintlayout.widget.ConstraintLayout
        android:layout_width="match_parent"
        android:layout_height="match_parent"
        tools:context=".MasterFragment">

        <TextView
 ...
            android:text="@{String.valueOf(n.number)}"
             />
```

代码中绑定xml的变量

```java
@Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        ViewModelProvider viewModelProvider = new ViewModelProvider(getActivity());
        MyViewModel myViewModel = viewModelProvider.get(MyViewModel.class);
        //与布局绑定
        FragmentMasterBinding binding = DataBindingUtil.inflate(inflater, R.layout.fragment_master, container, false);
        //操作布局里的变量
        binding.setN(myViewModel);
        binding.setLifecycleOwner(getViewLifecycleOwner());
        binding.nextButton.setOnClickListener(v->{
            Navigation.findNavController(v).navigate(R.id.action_masterFragment_to_detailFragment);
        });
        ...
        return binding.getRoot();
    }
```



### LifecycleEventObserver

实现接口

```java
public class MyChronometer extends Chronometer implements LifecycleEventObserver {
    private long elapsedTime;

    public MyChronometer(Context context) {
        super(context);
    }

    public MyChronometer(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    public MyChronometer(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }

    public MyChronometer(Context context, AttributeSet attrs, int defStyleAttr, int defStyleRes) {
        super(context, attrs, defStyleAttr, defStyleRes);
    }

    @Override
    public void onStateChanged(@NonNull LifecycleOwner lifecycleOwner, @NonNull Lifecycle.Event event) {
        switch (event){
            case ON_PAUSE:
                elapsedTime= SystemClock.elapsedRealtime()-getBase();
                stop();
                break;
            case ON_RESUME:
                setBase(SystemClock.elapsedRealtime()-elapsedTime);
                start();
                break;
            default:
                Log.i("event", "onStateChanged: "+event);
        }
    }
}

```

xml使用自定义组件

```xml
  <com.example.lifecyeledemo.MyChronometer
            android:id="@+id/myChronometer2"
            android:layout_width="wrap_content"
            android:layout_height="wrap_content"
            android:layout_marginBottom="21dp"
            app:layout_constraintBottom_toBottomOf="@+id/button_first"
            app:layout_constraintEnd_toStartOf="@+id/button_first"
            app:layout_constraintStart_toStartOf="parent" />
```

添加在Activity或Fragment添加观察者

```java
public void onViewCreated(@NonNull View view, Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        ...
        chronometer=getView().findViewById(R.id.myChronometer2);
        getActivity().getLifecycle().addObserver(chronometer);
    }
```





