package com.blogspot.rajbtc.smartrailgate;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.ImageView;
import android.widget.TextView;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class MainActivity extends AppCompatActivity {

    DatabaseReference dbRef=FirebaseDatabase.getInstance().getReference("Data");
    private TextView textView;
    private ImageView imageView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        textView=findViewById(R.id.tv);
        imageView=findViewById(R.id.iv);
        loadData();
    }

    void loadData(){
        dbRef.child("Train").addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                textView.setText((snapshot.getValue(String.class).equals("1")?"Train":"No train")+" is detected!");
                imageView.setImageResource(snapshot.getValue(String.class).equals("1")?R.drawable.train:R.drawable.no_train);
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });
    }


}