## Room基础

导入依赖

```groovy
   def room_version = "2.6.1"
   implementation "androidx.room:room-runtime:$room_version"
   annotationProcessor "androidx.room:room-compiler:$room_version"
```

定义实体

```java
@Entity(tableName = "word")
public class Word {
    @PrimaryKey(autoGenerate = true)
    private int id;

    @ColumnInfo(name = "english_word")
    private String englishWord;

    @ColumnInfo(name="chinese_meaning")
    private String chineseMeaning;

    public Word(String englishWord,String chineseMeaning) {
        this.englishWord = englishWord;
        this.chineseMeaning=chineseMeaning;
    }
	...定义所有Getter，Setter
}
```

定义DAO

```java
@Dao
public interface WordDao {
    @Insert
    void insertWords(Word... words);

    @Update
    void updateWords(Word... words);

    @Delete
    void deleteWords(Word... words);

    @Query("delete from word")
    void deleteAllWords();

    @Query("select * from word order by english_word asc")
    List<Word> getAllWords();
}
```

定义数据库

```java
@Database(entities = {Word.class} , version = 1 , exportSchema = false)
public abstract class WordDatabase extends RoomDatabase {
    public abstract WordDao getWordDao();
}
```

使用DAO

```java
wordDatabase= Room.databaseBuilder(this,WordDatabase.class,"word_database").allowMainThreadQueries().build();
wordDao=wordDatabase.getWordDao();
```

## LiveData监听变化

WordDao

```java
@Query("select * from word order by english_word asc")
LiveData<List<Word>> getAllWordsLife();
```

在MainActivity里为liveData添加观察

```java
//					查询出的words
liveData.observe(this, words -> {
            StringJoiner sj = new StringJoiner("\n","","\n");
            for(Word w : words){
                sj.add(w.toString());
            }
    		//更新UI
            tv.setText(sj.toString());
        });
```

## AndroidViewModel保存数据库对象

```java
public class WordViewModel extends AndroidViewModel {
    private WordDao wordDao;
    private LiveData<List<Word>> allWordsLife;

    public WordViewModel(@NonNull Application application) {
        super(application);
        WordDatabase wordDatabase=WordDatabase.getInstance(application);
        wordDao=wordDatabase.getWordDao();
        allWordsLife=wordDao.getAllWordsLife();
    }
    ...
}
```

## AsyncTask

```java
 static class DeleteAsyncTask extends AsyncTask<Word,Void,Void>{
        private WordDao wordDao;

        public DeleteAsyncTask(WordDao wordDao) {
            this.wordDao = wordDao;
        }
        @Override
        protected Void doInBackground(Word... words) {
            wordDao.deleteWords(words);
            return null;
        }
    }
```

